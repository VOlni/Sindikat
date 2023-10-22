package com.sindikat;

public class RestClientFactory {
    public IRestClient newRestClient(String implementation) {
        if (implementation.toLowerCase().equals("sindikat")){
            return new SindikatRestClient();
        }
	return new TelesignRestClientWrapper();
    }
}
