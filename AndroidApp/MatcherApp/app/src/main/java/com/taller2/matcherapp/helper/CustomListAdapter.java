package com.taller2.matcherapp.helper;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.drawable.Drawable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import com.taller2.matcherapp.R;
import com.taller2.matcherapp.app.AppController;

/**
 * Created by seba on 16/06/16.
 */
public class CustomListAdapter extends ArrayAdapter<String> {

    private final Activity context;
    private final String[] itemname;
    private final String[] itemphoto;

    public CustomListAdapter(Activity context, String[] itemname, String[] itemphoto) {
        super(context, R.layout.chatlist_view, itemname);
        this.context=context;
        this.itemname=itemname;
        this.itemphoto=itemphoto;
    }

    public View getView(int position, View view, ViewGroup parent) {
        LayoutInflater inflater=context.getLayoutInflater();
        View rowView=inflater.inflate(R.layout.chatlist_view, null,true);

        TextView txtTitle = (TextView) rowView.findViewById(R.id.Itemname);
        ImageView imageView = (ImageView) rowView.findViewById(R.id.icon);

        txtTitle.setText(itemname[position]);
        Bitmap profile_photo_map = AppController.getInstance().getBitmapImage(itemphoto[position]);
        imageView.setImageBitmap(profile_photo_map);
        return rowView;

    }
}
