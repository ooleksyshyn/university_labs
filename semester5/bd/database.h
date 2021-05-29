#ifndef DATABASE_PRAGMA_ONCE
#define DATABASE_PRAGMA_ONCE

#include <stdio.h>

#define S_FILE_DEFAULT "S.fl"
#define S_INDEX_TABLE_DEFAULT "S.ind"
#define R_FILE_DEFAULT "R.fl"
#define R_INDEX_TABLE_DEFAULT "R.ind"
#define SR_FILE_DEFAULT "SR.fl"

struct index_table {
    int id;
    int row;
    int first_node_row;
};

void print_index_table(struct index_table index);

struct db_session {
    FILE* employee_s_file;
    FILE* employee_s_index_table;
    FILE* room_s_file;
    FILE* room_s_index_table;
    FILE* sr_file;
};

struct db_session db_session_init(
        char* employee_s_file,
        char* employee_s_index_table,
        char* room_s_file,
        char* room_s_index_table,
        char* sr_file
);

void session_del(struct db_session*);

struct employee {
    int id;
    struct employee_data {
        char name[32];
        int passport_number;
    } data;
};

void print_employee(struct employee got);

struct room {
    int id;
    struct room_data {
        int number;
        int block_id;
    } data;
};

void print_room(struct room got);

struct working_node {
    struct working {
        int id_employee;
        int id_room;
        struct working_data{
            char name[32];
            int year;
        } data;
    } entity;

    int prev_row_by_employee;
    int prev_row_by_room;
    int next_row_by_employee;
    int next_row_by_room;
};

void print_working(struct working);

void print_working_node(struct working_node);

struct employee get_m_employee(struct db_session* session, int id);

struct room get_m_room(struct db_session* session, int id);

struct working get_s(struct db_session* session, int id_1, int id_2);

void del_m_employee(struct db_session* session, int id);

void del_m_room(struct db_session* session, int id);

void del_s(struct db_session* session, int id_1, int id_2);

int insert_m_employee(struct db_session* session, struct employee_data data);

int insert_m_room(struct db_session* session, struct room_data data);

int insert_s(struct db_session* session, int id_1, int id_2, struct working_data data);

int update_m_employee(struct db_session* session, int id, struct employee_data new_data);

int update_m_room(struct db_session* session, int id, struct room_data new_data);

int update_s(struct db_session* session, int id_1, int id_2, struct working_data new_data);

void ut_m_employee(struct db_session* session);

void ut_m_room(struct db_session* session);

void ut_s(struct db_session* session);

void reset_default_db();

#endif