package com.sindikat;
import com.telesign.RestClient;

public class TelesignRestClientWrapper implements IRestClient{
    
    private AssumeTelesignRestClient restClient;

    public TelesignRestClientWrapper(){
        AssumeTelesignRestClient rClient = new AssumeTelesignRestClient();
        restClient = rClient;
    }

    private class AssumeTelesignRestClient {
	// 
    }
    
    public String checkSimSwap() {
        return "sample check sim response";
    }
}
