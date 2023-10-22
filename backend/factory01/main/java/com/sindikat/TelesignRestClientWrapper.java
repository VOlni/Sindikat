package com.sindikat;

import com.telesign.RestClient;
public class TelesignRestClientWrapper implements IRestClient{

    private RestClient restClient;

    public TelesignRestClientWrapper(){
        RestClient rClient = new RestClient();
        restClient = rClient;
    }
    public String checkSimSwap() {
        return "sample check sim response";
    }
}
