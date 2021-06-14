package com.oop.service;

import com.oop.entities.dao.Account;
import com.oop.entities.dao.AccountStatus;
import com.oop.entities.dao.Transaction;
import com.oop.entities.dao.User;
import com.oop.repository.AccountRepository;
import com.oop.repository.TransactionRepository;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.springframework.test.context.junit.jupiter.SpringExtension;

import java.math.BigDecimal;
import java.util.Optional;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;

@ExtendWith(SpringExtension.class)
class TransactionServiceTest {
    @Mock
    private TransactionRepository transactionRepository;

    @InjectMocks
    private TransactionService transactionService;

    @Test
    void transaction() {
        Account account1 = new Account();
        account1.setId(22L);
        account1.setStatus(AccountStatus.ACTIVE);
        account1.setBalance(BigDecimal.valueOf(100));

        Account account2 = new Account();
        account2.setId(33L);
        account2.setStatus(AccountStatus.ACTIVE);
        account2.setBalance(BigDecimal.valueOf(100));

        BigDecimal amount = BigDecimal.valueOf(0);

        Transaction transaction = new Transaction();
        transaction.setAmount(amount);
        transaction.setFromAccount(account1);
        transaction.setToAccount(account2);

        when(transactionRepository.findById(transaction.getId())).thenReturn(Optional.of(transaction));

        transactionService.create(amount, account1, account2);

        assertEquals(BigDecimal.valueOf(0), transaction.getAmount());
        assertEquals(transaction.getId(), transaction.getId());
        assertEquals(account1, transaction.getFromAccount());
        assertEquals(account2, transaction.getToAccount());
        assertEquals(transaction.getCreatedAt(), transaction.getCreatedAt());
    }
}