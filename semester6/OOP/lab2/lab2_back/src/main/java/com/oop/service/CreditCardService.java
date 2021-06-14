package com.oop.service;

import com.oop.entities.dao.Account;
import com.oop.entities.dao.CreditCard;
import com.oop.entities.dao.User;
import com.oop.entities.request.CreditCardCreateRequest;
import com.oop.entities.request.CreditCardTransferRequest;
import com.oop.repository.CreditCardRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.math.BigDecimal;
import java.util.List;

@Service
@RequiredArgsConstructor
public class CreditCardService {

    private final UserService userService;
    private final AccountService accountService;
    private final CreditCardRepository creditCardRepository;

    @Transactional
    public CreditCard create(Long userId, CreditCardCreateRequest request) {
        User user = userService.getById(userId);

        Account account = accountService.create(user);

        CreditCard creditCard = new CreditCard();
        creditCard.setName(request.getName());
        creditCard.setAccount(account);
        return creditCardRepository.save(creditCard);
    }

    public List<CreditCard> getByUserId(Long userId) {
        return creditCardRepository.findByAccountUserId(userId);
    }

    public CreditCard getById(Long id) {
        return creditCardRepository.findById(id)
                .orElseThrow(() -> new RuntimeException(String.format("Can't find CreditCard by id=%d", id)));
    }

    public void transferMoney(CreditCardTransferRequest request) {
        CreditCard cardFrom = getById(request.getCardFromId());
        CreditCard cardTo = getById(request.getCardToId());

        accountService.transfer(cardFrom.getAccount().getId(), cardTo.getAccount().getId(), request.getAmount());
    }

    public void block(Long cardId) {
        CreditCard card = getById(cardId);

        accountService.block(card.getAccount());
    }

    public void unblock(Long cardId) {
        CreditCard card = getById(cardId);

        accountService.unblock(card.getAccount());
    }

    public void topUp(Long cardId, BigDecimal amount) {
        CreditCard card = getById(cardId);

        accountService.topUp(card.getAccount(), amount);
    }
}
