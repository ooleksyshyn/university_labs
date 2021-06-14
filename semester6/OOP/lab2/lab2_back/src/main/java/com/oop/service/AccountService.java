package com.oop.service;

import com.oop.entities.dao.Account;
import com.oop.entities.dao.AccountStatus;
import com.oop.entities.dao.User;
import com.oop.repository.AccountRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Isolation;
import org.springframework.transaction.annotation.Transactional;

import java.math.BigDecimal;

@Service
@RequiredArgsConstructor
public class AccountService {

    private final AccountRepository accountRepository;
    private final TransactionService transactionService;

    public Account getById(Long id) {
        return accountRepository.findById(id)
                .orElseThrow(() -> new RuntimeException(String.format("Can't find Account by id=%d", id)));
    }

    public Account block(Account account) {
        account.setStatus(AccountStatus.BLOCKED);
        return accountRepository.save(account);
    }

    public Account unblock(Account account) {
        account.setStatus(AccountStatus.ACTIVE);
        return accountRepository.save(account);
    }

    public Account create(User user) {
        Account account = new Account();
        account.setBalance(BigDecimal.ZERO);
        account.setStatus(AccountStatus.ACTIVE);
        account.setUser(user);

        return accountRepository.save(account);
    }

    @Transactional(isolation = Isolation.REPEATABLE_READ)
    public void topUp(Account account, BigDecimal amount) {

        if(!account.getStatus().equals(AccountStatus.ACTIVE)) {
            throw new RuntimeException("Account from status doesn't allow top up");
        }

        account.setBalance(account.getBalance().add(amount));

        accountRepository.save(account);
    }

    @Transactional(isolation = Isolation.REPEATABLE_READ)
    public void transfer(Long AccountFromId, Long AccountToId, BigDecimal amount) {
        Account accountFrom = getById(AccountFromId);
        Account accountTo = getById(AccountToId);

        if(accountFrom.getBalance().compareTo(amount) < 0) {
            throw new RuntimeException("Not enough money");
        }

        if(!accountFrom.getStatus().equals(AccountStatus.ACTIVE)) {
            throw new RuntimeException("Account from status doesn't allow transfer");
        }

        if(!accountTo.getStatus().equals(AccountStatus.ACTIVE)) {
            throw new RuntimeException("Account to status doesn't allow transfer");
        }

        accountFrom.setBalance(accountFrom.getBalance().subtract(amount));
        accountTo.setBalance(accountTo.getBalance().add(amount));

        accountRepository.save(accountFrom);
        accountRepository.save(accountTo);

        transactionService.create(amount, accountFrom, accountTo);
    }
}
