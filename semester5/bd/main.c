#include <stdio.h>

#include "database.h"

void demo_func() {
    struct db_session session = db_session_init(
            S_FILE_DEFAULT,
            S_INDEX_TABLE_DEFAULT,
            R_FILE_DEFAULT,
            R_INDEX_TABLE_DEFAULT,
            SR_FILE_DEFAULT
    );
    {
        struct employee_data to_insert = {"Ostap", 8060450};
        struct employee_data to_update = {"Oleksii", 5939693};
        insert_m_employee(&session, to_insert);
        insert_m_employee(&session, to_insert);
        update_m_employee(&session, 2, to_update);
        print_employee(get_m_employee(&session, 1));


        struct room_data to_insert_room = {2, 613};
        struct room_data to_update_room = {3, 621};
        insert_m_room(&session, to_insert_room);
        insert_m_room(&session, to_insert_room);
        update_m_room(&session, 1, to_update_room);

        struct working_data to_insert_model = {};
        insert_s(&session, 1, 2, to_insert_model);
        insert_s(&session, 1, 1, to_insert_model);
        insert_s(&session, 2, 1, to_insert_model);

        struct working_data to_update_model = {};
        update_s(&session, 1, 1, to_update_model);
        ut_s(&session);

//        del_s(&session, 1, 2);
//        del_s(&session, 1, 1);

        del_m_employee(&session, 2);
        del_m_room(&session, 1);

        ut_m_employee(&session);

        ut_m_room(&session);

        ut_s(&session);
        print_room(get_m_room(&session, 1));


        struct working got_model = get_s(&session, 1, 1);
        printf("room: %d \nemployee: %d \n",
               got_model.id_room,
               got_model.id_employee);
    }
}

int cmp_str(const char *lhs, const char *rhs, int size) {
    for (int i = 0
            ; i < size; ++i) {
        if (lhs[i] != rhs[i]) {
            return 0;
        }
    }
    return 1;
}


int main() {
    struct db_session session = db_session_init(
            S_FILE_DEFAULT,
            S_INDEX_TABLE_DEFAULT,
            R_FILE_DEFAULT,
            R_INDEX_TABLE_DEFAULT,
            SR_FILE_DEFAULT
    );
    printf("\nDormitory workings database");

    while(1) {
        printf("\n> ");
        char cmd[10];
        scanf("%s", cmd);
        if (cmp_str(cmd, "quit", 4)) {
            break;
        } else if (cmp_str(cmd, "reset", 5)) {
            reset_default_db();
            printf("\nDB reset");
        } else if (cmp_str(cmd, "insert_m", 8)) {
            char table[10];
            scanf("%s", table);
            if (cmp_str(table, "employee", 7)) {
                struct employee_data input;
                scanf("%s %d", input.name, &input.passport_number);
                int id = insert_m_employee(&session, input);
                printf("\ninserted with id=%d", id);
            } else if (cmp_str(table, "room", 4)) {
                struct room_data input;
                scanf("%d %d", &input.number, &input.block_id);
                int id = insert_m_room(&session, input);
                printf("\ninserted with id=%d", id);
            } else {
                printf("\n wrong table name");
            }
        } else if (cmp_str(cmd, "insert_s", 8)) {
            struct working input;
            scanf("%d %d", &input.id_employee, &input.id_room);
            if (insert_s(&session, input.id_employee, input.id_room, input.data)) {
                printf("\ninserted successfully");
            } else {
                printf("\nerror while inserting");
            }
        } else if (cmp_str(cmd, "get_m", 5)) {
            char table[10];
            scanf("%s", table);
            if (cmp_str(table, "employee", 7)) {
                int id;
                scanf("%d", &id);
                struct employee got = get_m_employee(&session, id);
                print_employee(got);
            } else if (cmp_str(table, "room", 4)) {
                int id;
                scanf("%d", &id);
                struct room got = get_m_room(&session, id);
                print_room(got);
            } else {
                printf("\n wrong table name");
            }
        } else if (cmp_str(cmd, "get_s", 5)) {
            int id1, id2;
            scanf("%d %d", &id1, &id2);
            struct working got = get_s(&session, id1, id2);

            if (got.id_employee == -1) {
                printf("\nno such working");
            } else {
                print_working(got);
            }
        } else if (cmp_str(cmd, "update_m", 8)) {
            char table[10];
            scanf("%s", table);
            int id;
            if (cmp_str(table, "employee", 7)) {
                struct employee_data input;
                scanf("%d %s %d", &id, input.name, &input.passport_number);
                update_m_employee(&session, id, input);
                printf("\nupdated");
            } else if (cmp_str(table, "room", 4)) {
                struct room_data input;
                scanf("%d %d %d", &id, &input.number, &input.block_id);
                update_m_room(&session, id, input);
                printf("\nupdated", id);
            } else {
                printf("\n wrong table name");
            }
        } else if (cmp_str(cmd, "update_s", 8)) {
            struct working input;
            scanf("%d %d", &input.id_employee, &input.id_room);
            if (update_s(&session, input.id_employee, input.id_room, input.data)) {
                printf("\nupdated successfully");
            } else {
                printf("\nerror while updating");
            }
        } else if (cmp_str(cmd, "del_m", 5)) {
            char table[10];
            scanf("%s", table);
            if (cmp_str(table, "employee", 7)) {
                int id;
                scanf("%d", &id);
                del_m_employee(&session, id);
                printf("deleted");
            } else if (cmp_str(table, "room", 4)) {
                int id;
                scanf("%d", &id);
                del_m_room(&session, id);
                printf("deleted");
            } else {
                printf("\n wrong table name");
            }
        } else if (cmp_str(cmd, "del_s", 5)) {
            int id1, id2;
            scanf("%d %d", &id1, &id2);
            del_s(&session, id1, id2);

            printf("deleted");
        } else if (cmp_str(cmd, "ut_m", 4)) {
            char table[10];
            scanf("%s", table);
            if (cmp_str(table, "employee", 7)) {
                ut_m_employee(&session);
            } else if (cmp_str(table, "room", 4)) {
                ut_m_room(&session);
            } else {
                printf("\n wrong table name");
            }
        } else if (cmp_str(cmd, "ut_s", 4)) {
            ut_s(&session);
        } else {
            printf("wrong command");
        }
    }

    session_del(&session);

    return 0;
}