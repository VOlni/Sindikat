package com.sindikat;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.channels.AsynchronousServerSocketChannel;
import java.nio.channels.AsynchronousSocketChannel;
import java.nio.channels.CompletionHandler;

public class Main {
    public static void main(String[] args) {

        int port = 5000;

        try {
            AsynchronousServerSocketChannel listener = AsynchronousServerSocketChannel.open().bind(new InetSocketAddress(port));

            System.out.println("Server listening on " + port);

            listener.accept("Client connection" , new CompletionHandler<AsynchronousSocketChannel,Object>(){

                @Override
                public void completed(AsynchronousSocketChannel result, Object attachment) {
                    System.out.println("Accepted a connection");

                    // accept the next connection
                    listener.accept("Client connection", this);

                    handle(result);
                }

                @Override
                public void failed(Throwable exc, Object attachment) {
                    System.out.println("Failed to accept connection");
                }

                public void handle(AsynchronousSocketChannel result) {
                    System.out.print(result);

                }
            });

            Thread.sleep(20000);
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}