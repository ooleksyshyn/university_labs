#include "database.h"

#define UTIL_OFFSET 2 * sizeof(int)
#define LAST_PK_OFFSET sizeof(int)
#define FILE_SIZE_OFFSET sizeof(int)

#define working_SIZE sizeof(struct working_node)
#define INDEX_ROW_SIZE sizeof(struct index_table)

#define NO_ROW -1

#define GET_FOR_M(row, session, table, entity_id) {                                     \
    fseek(session->table##_s_index_table, 0, SEEK_SET);                                 \
    int current_index_size;                                                             \
    fread(&current_index_size, FILE_SIZE_OFFSET, 1, session->table##_s_index_table);    \
    for (int i = 0; i < current_index_size; ++i) {                                      \
        struct index_table index;                                                       \
        fread(&index, INDEX_ROW_SIZE, 1, session->table##_s_index_table);               \
        if (index.id == entity_id) {                                                    \
            row = index.row;                                                            \
            fseek(session->table##_s_index_table, -(long)INDEX_ROW_SIZE, SEEK_CUR);     \
            break;                                                                      \
        }                                                                               \
    }                                                                                   \
}

#define INSERT_M(table) {                                                                           \
    reset_files(session);                                                                           \
    int cur_last_id, cur_size;                                                                      \
    fread(&cur_size, FILE_SIZE_OFFSET, 1, session->table##_s_file);                                 \
    fread(&cur_last_id, LAST_PK_OFFSET, 1, session->table##_s_file);                                \
    ++cur_last_id;                                                                                  \
    ++cur_size;                                                                                     \
    fseek(session->table##_s_file, 0L, SEEK_SET);                                                   \
    fwrite(&cur_size, FILE_SIZE_OFFSET, 1, session->table##_s_file);                                \
    fwrite(&cur_last_id, LAST_PK_OFFSET, 1, session->table##_s_file);                               \
                                                                                                    \
    fseek(session->table##_s_file, (cur_size - 1) * (int) sizeof(struct table) , SEEK_CUR);         \
    struct table to_insert = {cur_last_id, data};                                                   \
    fwrite(&to_insert, sizeof(struct table), 1, session->table##_s_file);                           \
                                                                                                    \
    int cur_index_size;                                                                             \
    fread(&cur_index_size, FILE_SIZE_OFFSET, 1, session->table##_s_index_table);                    \
    ++cur_index_size;                                                                               \
    fseek(session->table##_s_index_table, 0L, SEEK_SET);                                            \
    fwrite(&cur_index_size, FILE_SIZE_OFFSET, 1, session->table##_s_index_table);                   \
    fseek(session->table##_s_index_table, (cur_index_size - 1) * (int) INDEX_ROW_SIZE , SEEK_CUR);  \
    struct index_table index = {cur_last_id, cur_size - 1, -1};                                     \
    fwrite(&index, INDEX_ROW_SIZE, 1, session->table##_s_index_table);                              \
                                                                                                    \
    return cur_last_id;                                                                             \
}

#define GET_M(table) {                                                                  \
    reset_files(session);                                                               \
    int row = NO_ROW;                                                                   \
    GET_FOR_M(row, session, table, id);                                                 \
    struct table result = {-1};                                                         \
    if (row == NO_ROW) {                                                                \
        return result;                                                                  \
    }                                                                                   \
    fseek(session->table##_s_file, UTIL_OFFSET + row * sizeof(struct table), SEEK_SET); \
    fread(&result, sizeof(struct table), 1, session->table##_s_file);                   \
    return result;                                                                      \
}

#define UPDATE_M(table) {                                                               \
reset_files(session);                                                                   \
    int row = NO_ROW;                                                                   \
    GET_FOR_M(row, session, table, id);                                                 \
    if (row == NO_ROW) {                                                                \
        return -1;                                                                      \
    }                                                                                   \
    fseek(session->table##_s_file, UTIL_OFFSET + row * sizeof(struct table), SEEK_SET); \
    struct table to_insert = {id, new_data};                                            \
    fwrite(&to_insert, sizeof(struct table), 1, session->table##_s_file);               \
    return id;                                                                          \
}



struct db_session db_session_init(
        char* employee_s_file,
        char* employee_s_index_table,
        char* room_s_file,
        char* room_s_index_table,
        char* sr_file) {
    struct db_session result = {
            fopen(employee_s_file, "rb+"),
            fopen(employee_s_index_table, "rb+"),
            fopen(room_s_file, "rb+"),
            fopen(room_s_index_table, "rb+"),
            fopen(sr_file, "rb+")
    };
    return result;
}

void reset_files(struct db_session* session) {
    fseek(session->employee_s_file, 0L, SEEK_SET);
    fseek(session->employee_s_index_table, 0L, SEEK_SET);
    fseek(session->room_s_file, 0L, SEEK_SET);
    fseek(session->room_s_index_table, 0L, SEEK_SET);
    fseek(session->sr_file, 0L, SEEK_SET);
}

int insert_m_employee(struct db_session* session, struct employee_data data) {
    INSERT_M(employee)
}

struct employee get_m_employee(struct db_session* session, int id) {
    GET_M(employee)
}

int update_m_employee(struct db_session* session, int id, struct employee_data new_data) {
    UPDATE_M(employee)
}

struct room get_m_room(struct db_session *session, int id) {
    GET_M(room)
}

int insert_m_room(struct db_session *session, struct room_data data) {
    INSERT_M(room)
}

int update_m_room(struct db_session *session, int id, struct room_data new_data) {
    UPDATE_M(room);
}

#define MAP_NEW_RELATION(table, entity_id) {                                                        \
    int table##_index_size;                                                                         \
    fread(&table##_index_size, FILE_SIZE_OFFSET, 1, session->table##_s_index_table);                \
    for (int i = 0; i < table##_index_size; ++i) {                                                  \
        struct index_table index;                                                                   \
        fread(&index, INDEX_ROW_SIZE, 1, session->table##_s_index_table);                           \
        if (index.id == entity_id) {                                                                \
            if (index.first_node_row == NO_ROW) {                                                   \
                index.first_node_row = working_file_size;                                             \
                fseek(session->table##_s_index_table, -(long)INDEX_ROW_SIZE, SEEK_CUR);             \
                fwrite(&index, INDEX_ROW_SIZE, 1, session->table##_s_index_table);                  \
            } else {                                                                                \
                int last_row = index.first_node_row;                                                \
                struct working_node node;                                                             \
                while (last_row != -1) {                                                            \
                    table##_pre_last_row = last_row;                                                \
                    fseek(session->sr_file, FILE_SIZE_OFFSET + last_row * working_SIZE, SEEK_SET);    \
                    fread(&node, working_SIZE, 1, session->sr_file);                                  \
                    last_row = node.next_row_by_##table;                                            \
                    if (last_row == -1) {                                                           \
                         to_insert.prev_row_by_##table = table##_pre_last_row;                      \
                         node.next_row_by_##table = working_file_size;                                \
                         fseek(session->sr_file, -(long)working_SIZE, SEEK_CUR);                      \
                         fwrite(&node, working_SIZE, 1, session->sr_file);                            \
                    }                                                                               \
                }                                                                                   \
            }                                                                                       \
            break;                                                                                  \
        }                                                                                           \
                                                                                                    \
    }                                                                                               \
                                                                                                    \
}


int insert_s(struct db_session* session, int id_1, int id_2, struct working_data data) {
    if (get_s(session, id_1, id_2).id_employee != -1) {
        return 0;
    }
    reset_files(session);
    int working_file_size;
    fread(&working_file_size, FILE_SIZE_OFFSET, 1, session->sr_file);
    fseek(session->sr_file, 0, SEEK_SET);
    struct working_node to_insert = {
            {
                    id_1,
                    id_2,
                    data
            },
            NO_ROW,
            NO_ROW,
            NO_ROW,
            NO_ROW
    };
    int employee_pre_last_row = NO_ROW;
    MAP_NEW_RELATION(employee, id_1);

    int room_pre_last_row = NO_ROW;
    MAP_NEW_RELATION(room, id_2);

    fseek(session->sr_file, FILE_SIZE_OFFSET + working_file_size * working_SIZE, SEEK_SET);
    fwrite(&to_insert, working_SIZE, 1, session->sr_file);
    ++working_file_size;

    fseek(session->sr_file, 0, SEEK_SET);
    fwrite(&working_file_size, FILE_SIZE_OFFSET, 1, session->sr_file);
    return 1;
}

#define GET_FIRST_NODE(table, entity_id) {\
    reset_files(session);\
    int table##_index_size;                                                                        \
    fread(&table##_index_size, FILE_SIZE_OFFSET, 1, session->table##_s_index_table);               \
    for (int i = 0; i < table##_index_size; ++i) {                                                 \
        struct index_table index;                                                                  \
        fread(&index, INDEX_ROW_SIZE, 1, session->table##_s_index_table);                          \
        if (index.id == entity_id) {                                                               \
            first_node_row = index.first_node_row;                                                 \
            break;                                                                                 \
        }                                                                                          \
    }                                                                                              \
}

#define FIND_NODE_BY(table, cmp_table, entity_id) { \
    int next_node = first_node_row;\
    while (next_node != NO_ROW) {\
        fseek(session->sr_file, FILE_SIZE_OFFSET + next_node * working_SIZE, SEEK_SET);\
        fread(&current_node, working_SIZE, 1, session->sr_file);\
        next_node = current_node.next_row_by_##table;\
        if (current_node.entity.id_##cmp_table == entity_id) {                           \
            fseek(session->sr_file, -working_SIZE, SEEK_CUR);\
            break;\
        }\
    }           \
}

/// @brief Sets file pointer in position to rewrite relation

struct working_node get_s_node(struct db_session *session, int id_1, int id_2) {
    reset_files(session);
    struct working empty = {-1, -1};
    struct working_node empty_node = {empty};
    int first_node_row = NO_ROW;
    GET_FIRST_NODE(employee, id_1);
    if (first_node_row == NO_ROW) {
        return empty_node;
    }
    struct working_node current_node;
    FIND_NODE_BY(employee, room, id_2);

    if (current_node.entity.id_room == id_2) {
        return current_node;
    }

    return empty_node;
}
struct working get_s(struct db_session *session, int id_1, int id_2) {
    return get_s_node(session, id_1, id_2).entity;
}

#define UT_M_FILE(session, table) { \
    int size, last_id;\
    fread(&size, FILE_SIZE_OFFSET, 1, session->table##_s_file);\
    fread(&last_id, LAST_PK_OFFSET, 1, session->table##_s_file);\
    printf("::::::::::::File::" #table "::::::::::\nSize: %d \nLast_PK: %d\n-------------------------------\n", \
                size,               \
                last_id);\
    for (int i = 0; i < size; ++i) {\
        struct table got;\
        fread(&got, sizeof(struct table), 1, session->table##_s_file);                                          \
        printf("__Row__number__%d__\n", i);                        \
        print_##table(got);         \
    }\
    printf("::::::::::::::End::of::file::" #table "::::::::::\n");                     \
}

#define UT_M_INDEX(session, table) { \
    int size;\
    fread(&size, FILE_SIZE_OFFSET, 1, session->table##_s_index_table);\
    printf("::::::::::::Index::table::" #table "::::::::::\nSize: %d\n-------------------------------\n", size);\
    for (int i = 0; i < size; ++i) {\
        struct index_table got;\
        fread(&got, INDEX_ROW_SIZE, 1, session->table##_s_index_table);                                          \
        printf("__Row__number__%d__\n", i);                        \
        print_index_table(got);         \
    }\
    printf("::::::::::::::End::of::index::table::" #table "::::::::::\n");                     \
}

void ut_m_employee(struct db_session *session) {
    reset_files(session);
    UT_M_FILE(session, employee)
    UT_M_INDEX(session, employee)
}

void ut_m_room(struct db_session *session) {
    reset_files(session);
    UT_M_FILE(session, room)
    UT_M_INDEX(session, room)
}

void print_employee(struct employee got) {
    printf("id: %d \nname: %s \npassport number: %d \n",
           got.id,
           got.data.name,
           got.data.passport_number);
}

void print_room(struct room got) {
    printf("id: %d \nnumber: %d \nblock: %d \n",
           got.id,
           got.data.number,
           got.data.block_id);
}

void print_index_table(struct index_table index) {
    printf("id: %d\nrow: %d\nfirst_node_row: %d\n",
           index.id,
           index.row,
           index.first_node_row);
}

void ut_s(struct db_session *session) {
    reset_files(session);
    int size;
    fread(&size, FILE_SIZE_OFFSET, 1, session->sr_file);
    printf("::::::::::::SR::File::working::::::::::\nSize: %d\n-------------------------------\n", size);
    for (int i = 0; i < size; ++i) {
        struct working_node got;
        fread(&got, working_SIZE, 1, session->sr_file);
        printf("__Row__number__%d__\n", i);
        print_working_node(got);
    }
    printf("::::::::::::End::of::SR::File::working::::::::::\n");
}

void print_working_node(struct working_node node) {
    printf("employee id: %d\nroom id: %d \n"
           "Next by employee: %d \nPrev by employee: %d \n"
           "Next by room: %d \nPrev by room: %d \n",
           node.entity.id_employee,
           node.entity.id_room,
           node.next_row_by_employee,
           node.prev_row_by_employee,
           node.next_row_by_room,
           node.prev_row_by_room
    );
}

void print_working(struct working data) {
    printf("employee id: %d\nroom id: %d \n",
           data.id_employee, data.id_room
    );
}

int update_s(struct db_session *session, int id_1, int id_2, struct working_data new_data) {
    struct working_node found = get_s_node(session, id_1, id_2);
    if (found.entity.id_employee == -1) {
        return 0;
    }

    found.entity.data = new_data;

    if (fwrite(&found, working_SIZE, 1, session->sr_file)) {
        return 1;
    }

    return 0;
}

#define GET_INDEX_ROW_FOR_M(session, table, entity_id) {                                             \
    fseek(session->table##_s_index_table, 0, SEEK_SET);                                 \
    int current_index_size;                                                             \
    fread(&current_index_size, FILE_SIZE_OFFSET, 1, session->table##_s_index_table);    \
    for (int i = 0; i < current_index_size; ++i) {                                      \
        struct index_table index;                                                       \
        fread(&index, INDEX_ROW_SIZE, 1, session->table##_s_index_table);               \
        if (index.id == entity_id) {                                                           \
            index_row = index;                                                                    \
            fseek(session->table##_s_index_table, -(long)INDEX_ROW_SIZE, SEEK_CUR);                                 \
            break;                                                                      \
        }                                                                               \
    }                                                                                   \
}

#define GET_NODE(result, node, next_or_prev, table) { \
    fseek(session->sr_file, FILE_SIZE_OFFSET + node.next_or_prev##_row_by_##table * (long)working_SIZE, SEEK_SET);\
    fread(&result, working_SIZE, 1, session->sr_file);  \
    fseek(session->sr_file, -(long)working_SIZE, SEEK_CUR);\
}

#define INDEX_TABLE_REMAP(session, table, entity_id) {\
    struct index_table index_row;\
    GET_INDEX_ROW_FOR_M(session, table, entity_id)\
    deleted_pos = index_row.first_node_row;           \
    index_row.first_node_row = to_delete.next_row_by_##table; \
    fwrite(&index_row, INDEX_ROW_SIZE, 1, session->table##_s_index_table);\
}

#define REMAP_NODE_NEIGHBOUR(node, next_or_prev, prev_or_next, table) { \
    struct working_node neighbour_node;\
    GET_NODE(neighbour_node, node, next_or_prev, table)                 \
    deleted_pos = neighbour_node.prev_or_next##_row_by_##table;                                                       \
    neighbour_node.prev_or_next##_row_by_##table = node.prev_or_next##_row_by_##table;                                \
    fwrite(&neighbour_node, working_SIZE, 1, session->sr_file);                    \
}

#define REMAP_NEIGHBOURS_TO_NEW_POS(node, next_or_prev, prev_or_next, table) { \
    struct working_node neighbour_node;\
    GET_NODE(neighbour_node, node, next_or_prev, table)                 \
    neighbour_node.prev_or_next##_row_by_##table = deleted_pos;\
    fwrite(&neighbour_node, working_SIZE, 1, session->sr_file);                    \
}

#define INDEX_TABLE_SET_POS(session, table, entity_id) {\
    struct index_table index_row;\
    GET_INDEX_ROW_FOR_M(session, table, entity_id)      \
    index_row.first_node_row = deleted_pos;             \
    fwrite(&index_row, INDEX_ROW_SIZE, 1, session->table##_s_index_table);\
}

void del_s(struct db_session *session, int id_1, int id_2) {
    reset_files(session);

    struct working_node to_delete = get_s_node(session, id_1, id_2);

    if (to_delete.entity.id_employee == -1) {
        return;
    }

    int deleted_pos = NO_ROW;
    if (to_delete.prev_row_by_employee == NO_ROW) {
        INDEX_TABLE_REMAP(session, employee, id_1);
    } else {
        REMAP_NODE_NEIGHBOUR(to_delete, prev, next, employee)
    }

    if (to_delete.prev_row_by_room == NO_ROW) {
        INDEX_TABLE_REMAP(session, room, id_2);
    } else {
        REMAP_NODE_NEIGHBOUR(to_delete, prev, next, room)
    }

    if (to_delete.next_row_by_employee != NO_ROW) {
        REMAP_NODE_NEIGHBOUR(to_delete, next, prev, employee)
    }

    if (to_delete.next_row_by_room != NO_ROW) {
        REMAP_NODE_NEIGHBOUR(to_delete, next, prev, room)
    }

    int size;
    reset_files(session);
    fread(&size, FILE_SIZE_OFFSET, 1, session->sr_file);
    fseek(session->sr_file, (size - 1) * (long)working_SIZE, SEEK_CUR);
    struct working_node to_replace;
    fread(&to_replace, working_SIZE, 1, session->sr_file);
    if (size != deleted_pos + 1) {
        int id_employee = to_replace.entity.id_employee;
        int id_room = to_replace.entity.id_room;

        reset_files(session);

        if (to_replace.prev_row_by_employee == NO_ROW) {
            INDEX_TABLE_SET_POS(session, employee, id_employee);
        } else {
            REMAP_NEIGHBOURS_TO_NEW_POS(to_replace, prev, next, employee)
        }

        if (to_replace.prev_row_by_room == NO_ROW) {
            INDEX_TABLE_SET_POS(session, room, id_room);
        } else {
            REMAP_NEIGHBOURS_TO_NEW_POS(to_replace, prev, next, room)
        }

        if (to_replace.next_row_by_employee != NO_ROW) {
            REMAP_NEIGHBOURS_TO_NEW_POS(to_replace, next, prev, employee)
        }

        if (to_replace.next_row_by_room != NO_ROW) {
            REMAP_NEIGHBOURS_TO_NEW_POS(to_replace, next, prev, room)
        }
    }


    --size;
    fseek(session->sr_file,0, SEEK_SET);
    fwrite(&size, FILE_SIZE_OFFSET, 1, session->sr_file);
    fseek(session->sr_file,deleted_pos * (long)working_SIZE, SEEK_CUR);
    fwrite(&to_replace, working_SIZE, 1, session->sr_file);

}

#define DEL_M(main, secondary) { \
    reset_files(session);\
    int first_node_row = NO_ROW;\
    do {\
        GET_FIRST_NODE(main, id);\
        if (first_node_row != NO_ROW) {\
            fseek(session->sr_file, FILE_SIZE_OFFSET + first_node_row * working_SIZE, SEEK_SET);\
            struct working_node to_delete;\
            fread(&to_delete, working_SIZE, 1, session->sr_file);\
            del_s(session, id, to_delete.entity.id_##secondary);\
        }\
    } while (first_node_row != NO_ROW);\
    int row = NO_ROW;\
    GET_FOR_M(row, session, main, id)\
    int cur_pos = ftell(session->main##_s_index_table);\
    int deleted_index_row = (cur_pos - FILE_SIZE_OFFSET) / INDEX_ROW_SIZE;\
    \
    if (row != NO_ROW) {\
        int size = 0;\
        fread(&size, FILE_SIZE_OFFSET, 1 , session->main##_s_file);\
        --size;\
        fseek(session->main##_s_file, UTIL_OFFSET + (size) * sizeof(struct main), SEEK_SET);\
        struct main to_replace;\
        fread(&to_replace, sizeof(struct main), 1, session->main##_s_file);\
        fseek(session->main##_s_file, 0, SEEK_SET);\
        fwrite(&size, FILE_SIZE_OFFSET, 1, session->main##_s_file);\
        fseek(session->main##_s_file, UTIL_OFFSET + row * sizeof(struct main), SEEK_SET);\
        fwrite(&to_replace, sizeof(struct main), 1, session->main##_s_file);\
        struct index_table index_row;\
        GET_INDEX_ROW_FOR_M(session, main, to_replace.id)\
        index_row.row = row;\
        fwrite(&index_row, INDEX_ROW_SIZE, 1, session->main##_s_index_table);\
        \
        for (int i = deleted_index_row; i < size; ++i) {\
        \
            fseek(session->main##_s_index_table, FILE_SIZE_OFFSET + (i + 1) * INDEX_ROW_SIZE, SEEK_SET);\
            fread(&index_row, INDEX_ROW_SIZE, 1, session->main##_s_index_table);\
            \
            fseek(session->main##_s_index_table, FILE_SIZE_OFFSET + (i) * INDEX_ROW_SIZE, SEEK_SET);\
            fwrite(&index_row, INDEX_ROW_SIZE, 1, session->main##_s_index_table);\
        \
        }\
        \
        fseek(session->main##_s_index_table, 0, SEEK_SET);\
        \
        fwrite(&size, FILE_SIZE_OFFSET, 1, session->main##_s_index_table);\
    }\
}

void del_m_employee(struct db_session *session, int id) {
    DEL_M(employee, room)
}

void del_m_room(struct db_session *session, int id) {
    DEL_M(room, employee)
}

void reset_default_db() {
    FILE* s = fopen(S_FILE_DEFAULT, "w");
    FILE* si = fopen(S_INDEX_TABLE_DEFAULT, "w");
    FILE* r = fopen(R_FILE_DEFAULT, "w");
    FILE* ri = fopen(R_INDEX_TABLE_DEFAULT, "w");
    FILE* sr = fopen(SR_FILE_DEFAULT, "w");

    int zero = 0;
    int ind = 0;
    fwrite(&zero, sizeof(int), 1, s);
    fwrite(&ind, sizeof(int), 1, s);

    fwrite(&zero, sizeof(int), 1, si);

    fwrite(&zero, sizeof(int), 1, r);
    fwrite(&ind, sizeof(int), 1, r);

    fwrite(&zero, sizeof(int), 1, ri);

    fwrite(&zero, sizeof(int), 1, sr);
    fclose(s);
    fclose(si);
    fclose(r);
    fclose(ri);
    fclose(sr);
}

void session_del(struct db_session *session) {
    fclose(session->employee_s_index_table);
    fclose(session->employee_s_file);
    fclose(session->sr_file);
    fclose(session->room_s_index_table);
    fclose(session->room_s_file);
}









