package com.oop.mappers;

import com.oop.entities.dao.Account;
import com.oop.entities.dao.CreditCard;
import com.oop.entities.response.AccountResponse;
import com.oop.entities.response.CreditCardResponse;
import java.util.ArrayList;
import java.util.List;
import javax.annotation.processing.Generated;

@Generated(
    value = "org.mapstruct.ap.MappingProcessor",
    date = "2021-06-14T16:03:06+0300",
    comments = "version: 1.4.1.Final, compiler: javac, environment: Java 13.0.5 (Azul Systems, Inc.)"
)
public class CreditCardMapperImpl implements CreditCardMapper {

    @Override
    public List<CreditCardResponse> toResponses(List<CreditCard> creditCards) {
        if ( creditCards == null ) {
            return null;
        }

        List<CreditCardResponse> list = new ArrayList<CreditCardResponse>( creditCards.size() );
        for ( CreditCard creditCard : creditCards ) {
            list.add( toResponse( creditCard ) );
        }

        return list;
    }

    @Override
    public CreditCardResponse toResponse(CreditCard creditCard) {
        if ( creditCard == null ) {
            return null;
        }

        CreditCardResponse creditCardResponse = new CreditCardResponse();

        creditCardResponse.setId( creditCard.getId() );
        creditCardResponse.setName( creditCard.getName() );
        creditCardResponse.setAccount( accountToAccountResponse( creditCard.getAccount() ) );

        return creditCardResponse;
    }

    protected AccountResponse accountToAccountResponse(Account account) {
        if ( account == null ) {
            return null;
        }

        AccountResponse accountResponse = new AccountResponse();

        accountResponse.setId( account.getId() );
        accountResponse.setBalance( account.getBalance() );
        accountResponse.setStatus( account.getStatus() );

        return accountResponse;
    }
}
