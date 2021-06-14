package com.oop.client;

import feign.Headers;
import org.keycloak.representations.AccessTokenResponse;
import org.springframework.cloud.openfeign.FeignClient;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

import java.util.Map;

import static org.springframework.http.MediaType.APPLICATION_FORM_URLENCODED_VALUE;

@FeignClient(value = "KeycloakClient", url = "${keycloak.authServerUrl}")
public interface KeycloakClient {
    @Headers("Content-Type: application/x-www-form-urlencoded")
    @RequestMapping(method = RequestMethod.POST, value = "/realms/{realm}/protocol/openid-connect/token", consumes = APPLICATION_FORM_URLENCODED_VALUE)
    AccessTokenResponse getAccessToken(@PathVariable("realm") String param,
                            @RequestBody Map<String, ?> formParams);
}
