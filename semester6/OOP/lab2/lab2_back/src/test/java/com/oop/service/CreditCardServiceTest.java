package com.oop.service;

import com.oop.entities.dao.Account;
import com.oop.entities.dao.CreditCard;
import com.oop.entities.dao.User;
import com.oop.entities.request.CreditCardCreateRequest;
import com.oop.entities.request.CreditCardTransferRequest;
import com.oop.repository.CreditCardRepository;
import com.oop.utils.TestData;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.ArgumentCaptor;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.springframework.test.context.junit.jupiter.SpringExtension;

import java.math.BigDecimal;
import java.util.Optional;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

@ExtendWith(SpringExtension.class)
public class CreditCardServiceTest {
    @Mock
    private UserService userService;

    @Mock
    private AccountService accountService;

    @Mock
    private CreditCardRepository creditCardRepository;

    @InjectMocks
    private CreditCardService creditCardService;

    @Test
    void create() {
        CreditCardCreateRequest request = TestData.getCreditCardCreateRequest();
        User user = new User();
        user.setId(22L);

        Account account = new Account();

        when(userService.getById(user.getId())).thenReturn(user);
        when(accountService.create(user)).thenReturn(account);

        creditCardService.create(user.getId(), request);

        ArgumentCaptor<CreditCard> creditCardArgumentCaptor = ArgumentCaptor.forClass(CreditCard.class);
        verify(creditCardRepository).save(creditCardArgumentCaptor.capture());

        CreditCard creditCard = creditCardArgumentCaptor.getValue();

        assertEquals(request.getName(), creditCard.getName());
        assertEquals(account, creditCard.getAccount());
    }

    @Test
    void transferMoney() {
        CreditCard card1 = new CreditCard();
        Account account1 = new Account();
        account1.setId(22L);
        card1.setAccount(account1);

        CreditCard card2 = new CreditCard();
        Account account2 = new Account();
        account2.setId(23L);
        card2.setAccount(account2);

        CreditCardTransferRequest request = new CreditCardTransferRequest();
        request.setAmount(BigDecimal.valueOf(12));
        request.setCardFromId(1L);
        request.setCardToId(2L);

        when(creditCardRepository.findById(request.getCardFromId())).thenReturn(Optional.of(card1));
        when(creditCardRepository.findById(request.getCardToId())).thenReturn(Optional.of(card2));

        creditCardService.transferMoney(request);

        verify(accountService).transfer(account1.getId(), account2.getId(), request.getAmount());
    }
}
