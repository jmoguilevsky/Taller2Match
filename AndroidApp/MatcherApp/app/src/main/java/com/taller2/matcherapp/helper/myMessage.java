package com.taller2.matcherapp.helper;

public class myMessage {
    private String fromID, message;
    private boolean isSelf;

    public myMessage() {
    }

    public myMessage(String fromID, String message, boolean isSelf) {
        this.fromID = fromID;
        this.message = message;
        this.isSelf = isSelf;
    }

    public String getFromID() {
        return fromID;
    }

    public void setFromID(String fromID) {
        this.fromID = fromID;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public boolean isSelf() {
        return isSelf;
    }

    public void setSelf(boolean isSelf) {
        this.isSelf = isSelf;
    }

}