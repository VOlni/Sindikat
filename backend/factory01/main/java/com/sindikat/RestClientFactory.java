package com.sindikat;

public class RestClientFactory {

    public IRestClient newInstance(String implementation) {
        if (implementation.toLowerCase() == "sindikat"){
            return SindikatRestClient;
        } else if (implementation.toLowerCase() == "telesign") {
            return TelesignRestClientWrapper;
        }
    }
}
