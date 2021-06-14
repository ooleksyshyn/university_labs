package com.oop.entities.response;

import com.oop.entities.dao.AccountStatus;
import lombok.Data;

import java.math.BigDecimal;

@Data
public class AccountResponse {
    private Long id;
    private BigDecimal balance;
    private AccountStatus status;
}
