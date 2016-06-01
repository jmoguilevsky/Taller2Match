package com.taller2.matcherapp.helper;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

import java.util.HashMap;

/**
 * Created by seba on 24/04/16.
 */
public class SQLiteHandler extends SQLiteOpenHelper {

    private static final String TAG = SQLiteHandler.class.getSimpleName();

    // All Static variables
    // Database Version
    private static final int DATABASE_VERSION = 1;

    // Database Name
    private static final String DATABASE_NAME = "matcher";

    // Login table name
    private static final String TABLE_USER = "user";

    // Login Table Columns names
    private static final String KEY_ID = "id";
    private static final String KEY_NAME = "name";
    private static final String KEY_ALIAS = "alias";
    private static final String KEY_GENDER = "gender";
    private static final String KEY_EMAIL = "email";
    private static final String KEY_INTERESTS = "interests";
    private static final String KEY_PHOTO = "photo";
    private static final String KEY_LOCATION = "location";
    private static final String KEY_TOKEN = "token";

    public SQLiteHandler(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    // Creating Tables
    @Override
    public void onCreate(SQLiteDatabase db) {
        String CREATE_LOGIN_TABLE = "CREATE TABLE " + TABLE_USER + "(" +
                KEY_ID + " INTEGER PRIMARY KEY," +
                KEY_NAME + " TEXT," +
                KEY_ALIAS + " TEXT," +
                KEY_GENDER + " TEXT," +
                KEY_EMAIL + " TEXT UNIQUE," +
                KEY_INTERESTS + " TEXT," +
                KEY_PHOTO + " TEXT," +
                KEY_LOCATION + " TEXT," +
                KEY_TOKEN + " TEXT" + ")";
        db.execSQL(CREATE_LOGIN_TABLE);

        Log.d(TAG, "Database tables created");
    }

    // Upgrading database
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        // This database is only a cache for online data, so its upgrade policy is
        // to simply to discard the data and start over

        // Drop older table if existed
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_USER);
        // Create tables again
        onCreate(db);
    }

    /**
     * Storing user details in database
     * */
    public void addUser(String name, String alias, String gender, String email, String interests,
                        String profile_photo, String location, String token) {
        SQLiteDatabase db = this.getWritableDatabase();

        ContentValues values = new ContentValues();
        values.put(KEY_NAME, name); // Name
        values.put(KEY_ALIAS, alias); // Alias
        values.put(KEY_GENDER, gender); // User gender
        values.put(KEY_EMAIL, email); // Email
        values.put(KEY_INTERESTS, interests); // Interests
        values.put(KEY_PHOTO, profile_photo); // Profile picture
        values.put(KEY_LOCATION, location); // Location: lat and long
        values.put(KEY_TOKEN, token); // Token

        // Inserting Row
        long id = db.insert(TABLE_USER, null, values);
        db.close(); // Closing database connection

        Log.d(TAG, "New user inserted into sqlite: ");
    }

    /**
     * Getting user data from database
     * */
    public HashMap<String, String> getUserDetails() {
        HashMap<String, String> user = new HashMap<String, String>();
        String selectQuery = "SELECT  * FROM " + TABLE_USER;

        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.rawQuery(selectQuery, null);
        // Move to first row
        cursor.moveToFirst();
        if (cursor.getCount() > 0) {
            user.put("name", cursor.getString(1));
            user.put("alias",cursor.getString(2));
            user.put("gender", cursor.getString(3));
            user.put("email", cursor.getString(4));
            user.put("interests", cursor.getString(5));
            user.put("photo", cursor.getString(6));
            user.put("location", cursor.getString(7));
            user.put("token",cursor.getString(8));
        }
        cursor.close();
        db.close();
        // return user
        Log.d(TAG, "Fetching user from Sqlite: ");

        return user;
    }

    // Delete all rows from the database.
    public void deleteUsers() {
        SQLiteDatabase db = this.getWritableDatabase();
        // Delete All Rows
        db.delete(TABLE_USER, null, null);
        db.close();

        Log.d(TAG, "Deleted all user info from sqlite");
    }

}
