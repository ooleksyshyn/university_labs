CREATE TABLE users (
    id          bigserial       primary key,
    first_name  varchar(128)    not null,
    last_name   varchar(128)    not null,
    username    varchar(128)    not null,
    keycloak_id varchar(256)
);

CREATE TABLE account (
    id      bigserial       primary key,
    user_id int8            not null REFERENCES users(id),
    balance numeric         not null,
    status  varchar(128)    not null
);

CREATE TABLE credit_card (
    id              bigserial       primary key,
    name            varchar(128)    not null,
    account_id int8            not null    unique REFERENCES account(id)
);

CREATE TABLE transaction(
    id                  bigserial   primary key,
    from_account_id     int8        not null REFERENCES account(id),
    to_account_id       int8        not null REFERENCES account(id),
    amount              numeric     not null,
    created_at          timestamp   not null
);