package com.oop.service;

import com.oop.entities.dao.Account;
import com.oop.entities.dao.Transaction;
import com.oop.repository.TransactionRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.math.BigDecimal;

@Service
@RequiredArgsConstructor
public class TransactionService {
    private final TransactionRepository transactionRepository;

    public Transaction create(BigDecimal amount, Account accountFrom, Account accountTo) {
        Transaction transaction = new Transaction();
        transaction.setAmount(amount);
        transaction.setFromAccount(accountFrom);
        transaction.setToAccount(accountTo);

        return transactionRepository.save(transaction);
    }
}
