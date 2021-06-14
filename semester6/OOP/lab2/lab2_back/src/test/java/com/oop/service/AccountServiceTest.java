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

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.mockito.Mockito.*;

@ExtendWith(SpringExtension.class)
public class AccountServiceTest {

    @Mock
    private AccountRepository accountRepository;

    @InjectMocks
    private AccountService accountService;

    @Test
    void transfer() {
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

        when(accountRepository.findById(account1.getId())).thenReturn(Optional.of(account1));
        when(accountRepository.findById(account2.getId())).thenReturn(Optional.of(account2));

        /*accountService.transfer(account1.getId(), account2.getId(), amount);

        verify(accountRepository).save(account1);
        verify(accountRepository).save(account2);*/

        assertEquals(BigDecimal.valueOf(100).subtract(amount), account1.getBalance());
        assertEquals(BigDecimal.valueOf(100).add(amount), account2.getBalance());
    }

    @Test
    void createAccount() {

        User user = new User();
        user.setId(22L);

        Account account1 = new Account();
        account1.setStatus(AccountStatus.ACTIVE);
        account1.setUser(user);
        account1.setBalance(BigDecimal.valueOf(0));

        when(accountRepository.findById(account1.getId())).thenReturn(Optional.of(account1));

        accountService.create(user);

        verify(accountRepository).save(account1);

        assertEquals(AccountStatus.ACTIVE, account1.getStatus());
        assertEquals(user, account1.getUser());
    }

    @Test
    void block() {
        Account account1 = new Account();
        account1.setId(22L);
        account1.setStatus(AccountStatus.ACTIVE);
        account1.setBalance(BigDecimal.valueOf(100));

        when(accountRepository.findById(account1.getId())).thenReturn(Optional.of(account1));

        accountService.block(account1);

        verify(accountRepository).save(account1);

        assertEquals(AccountStatus.BLOCKED, account1.getStatus());
    }

    @Test
    void unblock() {
        Account account1 = new Account();
        account1.setId(22L);
        account1.setStatus(AccountStatus.BLOCKED);
        account1.setBalance(BigDecimal.valueOf(100));

        when(accountRepository.findById(account1.getId())).thenReturn(Optional.of(account1));

        accountService.unblock(account1);

        verify(accountRepository).save(account1);

        assertEquals(AccountStatus.ACTIVE, account1.getStatus());
    }

    @Test
    void transfer_notEnoughMoney() {
        Account account1 = new Account();
        account1.setId(22L);
        account1.setStatus(AccountStatus.ACTIVE);
        account1.setBalance(BigDecimal.valueOf(10));

        Account account2 = new Account();
        account2.setId(33L);
        account2.setStatus(AccountStatus.ACTIVE);
        account2.setBalance(BigDecimal.valueOf(100));

        BigDecimal amount = BigDecimal.valueOf(22);

        when(accountRepository.findById(account1.getId())).thenReturn(Optional.of(account1));
        when(accountRepository.findById(account2.getId())).thenReturn(Optional.of(account2));

        assertThrows(RuntimeException.class, () -> accountService.transfer(account1.getId(), account2.getId(), amount));
    }

    @Test
    void transfer_notActive() {
        Account account1 = new Account();
        account1.setId(22L);
        account1.setStatus(AccountStatus.ACTIVE);
        account1.setBalance(BigDecimal.valueOf(100));

        Account account2 = new Account();
        account2.setId(33L);
        account2.setStatus(AccountStatus.BLOCKED);
        account2.setBalance(BigDecimal.valueOf(100));

        BigDecimal amount = BigDecimal.valueOf(22);

        when(accountRepository.findById(account1.getId())).thenReturn(Optional.of(account1));
        when(accountRepository.findById(account2.getId())).thenReturn(Optional.of(account2));

        assertThrows(RuntimeException.class, () -> accountService.transfer(account1.getId(), account2.getId(), amount));
    }
}
