package com.misctools.audiotoolkit;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.util.Locale;

import android.app.Activity;
import android.app.ActionBar;
import android.app.Fragment;
import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.support.v13.app.FragmentPagerAdapter;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v4.view.ViewPager;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;
import android.widget.ScrollView;
import android.widget.TextView;


public class MainActivity extends Activity implements ActionBar.TabListener {

    /**
     * The {@link android.support.v4.view.PagerAdapter} that will provide
     * fragments for each of the sections. We use a
     * {@link FragmentPagerAdapter} derivative, which will keep every
     * loaded fragment in memory. If this becomes too memory intensive, it
     * may be best to switch to a
     * {@link android.support.v13.app.FragmentStatePagerAdapter}.
     */
    SectionsPagerAdapter mSectionsPagerAdapter;

    final private static String TAG = "AudioToolkit";
    /**
     * The {@link ViewPager} that will host the section contents.
     */
    ViewPager mViewPager;
	MsgHandler mHandler = new MsgHandler();
	CmdRunner mRunners[] = {null, null, null, null, null};

    private static final int MSG_OUTPUT_UPDATE = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Set up the action bar.
        final ActionBar actionBar = getActionBar();
        actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_TABS);

        // Create the adapter that will return a fragment for each of the three
        // primary sections of the activity.
        mSectionsPagerAdapter = new SectionsPagerAdapter(getFragmentManager());

        // Set up the ViewPager with the sections adapter.
        mViewPager = (ViewPager) findViewById(R.id.pager);
        mViewPager.setAdapter(mSectionsPagerAdapter);

        // When swiping between different sections, select the corresponding
        // tab. We can also use ActionBar.Tab#select() to do this if we have
        // a reference to the Tab.
        mViewPager.setOnPageChangeListener(new ViewPager.SimpleOnPageChangeListener() {
            @Override
            public void onPageSelected(int position) {
                actionBar.setSelectedNavigationItem(position);
            }
        });

        // For each of the sections in the app, add a tab to the action bar.
        for (int i = 0; i < mSectionsPagerAdapter.getCount(); i++) {
            // Create a tab with text corresponding to the page title defined by
            // the adapter. Also specify this Activity object, which implements
            // the TabListener interface, as the callback (listener) for when
            // this tab is selected.
            actionBar.addTab(
                    actionBar.newTab()
                            .setText(mSectionsPagerAdapter.getPageTitle(i))
                            .setTabListener(this));
        }
        
        actionBar.selectTab(actionBar.getTabAt(0));
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    @Override
    public void onTabSelected(ActionBar.Tab tab, FragmentTransaction fragmentTransaction) {
        // When the given tab is selected, switch to the corresponding page in
        // the ViewPager.
    	int pos = tab.getPosition();
        mViewPager.setCurrentItem(pos);
        String result = null;
        
        Log.i(TAG, "onTabSelected: " + pos + "\r\n");

		String sCmds[] = {
		 	"/system/bin/dumpsys media.audio_policy",
			"/system/bin/dumpsys media.audio_flinger",
			"/system/bin/dumpsys audio",
			"/system/bin/cat /proc/asound/cards",
			"/system/bin/getevent /dev/input/event10"};
	
		if(mRunners[pos]!=null && !mRunners[pos].isAlive()){
			mSectionsPagerAdapter.clearText(pos);
			mRunners[pos].exit();
			Log.i(TAG, "Recreate the worker Thread");
		}else
			Log.i(TAG, "Create the worker Thread");
		
		mRunners[pos] = new CmdRunner(sCmds[pos], pos);
		mRunners[pos].start();
    }

    @Override
    public void onTabUnselected(ActionBar.Tab tab, FragmentTransaction fragmentTransaction) {
    }

    @Override
    public void onTabReselected(ActionBar.Tab tab, FragmentTransaction fragmentTransaction) {
    }

	private class CmdRunner extends Thread {
		private String mCmd;
		private int mID;
		private boolean mExit = false;
		
        public CmdRunner(String cmd, int id) {
            super("AudioToolkit");
			mCmd = cmd;
			mID = id;
        }

        @Override
        public void run() {
			Process process = null;
			DataInputStream is = null;

			try{
				process = Runtime.getRuntime().exec(mCmd);
				is = new DataInputStream(process.getInputStream());
				
				String tmpresult = null;
				BufferedReader reader = new BufferedReader(new InputStreamReader(is));
				while ((tmpresult = reader.readLine()) != null && !mExit) {
					tmpresult += "\r\n";
					mHandler.sendMessage(mID, tmpresult);
				}	  
			} catch (Exception e) {
			}  
			finally {
				try {
					if (is != null){
						is.close();
					}
					process.destroy();
				} catch (Exception e) {
				}
			}
			Log.i(TAG, mCmd + " Exit!!");
        }

		public void exit(){
			mExit = true;
			try {
				join();
			}catch (Exception e){
				Log.i(TAG, "Fatal Error");
			}
		}
    }


    /** Handles internal volume messages in separate volume thread. */
    private class MsgHandler extends Handler {

        public void sendMessage(int id, String text) {
			mHandler.sendMessage(mHandler.obtainMessage(MSG_OUTPUT_UPDATE, 
				id, 0, text));
        }

        @Override
        public void handleMessage(Message msg) {
            if (msg.what == MSG_OUTPUT_UPDATE) {
				String logline = (String)msg.obj;
				int pos = msg.arg1;
				//Log.i(TAG, pos + " : " + logline);
				mSectionsPagerAdapter.addText(pos, logline);
            }
        }
    }

    /**
     * A {@link FragmentPagerAdapter} that returns a fragment corresponding to
     * one of the sections/tabs/pages.
     */
    public class SectionsPagerAdapter extends FragmentPagerAdapter {

    	private PlaceholderFragment mFragment[] = {null, null, null, null, null};
        public SectionsPagerAdapter(FragmentManager fm) {
            super(fm);
        }

        @Override
        public Fragment getItem(int position) {
            // getItem is called to instantiate the fragment for the given page.
            // Return a PlaceholderFragment (defined as a static inner class below).
        	 mFragment[position] = PlaceholderFragment.newInstance(position);
            return mFragment[position];
        }

        public boolean addText(int position, String text){
        	if(mFragment[position] != null){
        		mFragment[position].addText(text);
        		return true;
        	} else
        		return false;
        }

		public void clearText(int position){
			if(mFragment[position] != null)
				mFragment[position].clearText();
		}
        
        @Override
        public int getCount() {
            // Show 5 total pages.
            return 4;
        }

        @Override
        public CharSequence getPageTitle(int position) {
            Locale l = Locale.getDefault();
            switch (position) {
                case 0:
                    return getString(R.string.title_section1).toUpperCase(l);
                case 1:
                    return getString(R.string.title_section2).toUpperCase(l);
                case 2:
                    return getString(R.string.title_section3).toUpperCase(l);
                case 3:
                    return getString(R.string.title_section4).toUpperCase(l);   
				case 4:
					return getString(R.string.title_section5).toUpperCase(l);
            }
            return null;
        }
    }

    /**
     * A placeholder fragment containing a simple view.
     */
    public static class PlaceholderFragment extends Fragment {
        /**
         * The fragment argument representing the section number for this
         * fragment.
         */
        //private static final String ARG_SECTION_NUMBER = "section_number";

        /**
         * Returns a new instance of this fragment for the given section
         * number.
         */
        private TextView mTv = null;
        
        public static PlaceholderFragment newInstance(int position) {
        	
        	PlaceholderFragment fragment = new PlaceholderFragment();

            return fragment;
        }

        public void addText(String text){
        	mTv.setText(mTv.getText() + text);
        }
		public void clearText(){
			mTv.setText("");
		}
        
        public PlaceholderFragment() {
        }

        @Override
        public View onCreateView(LayoutInflater inflater, ViewGroup container,
                Bundle savedInstanceState) {
        	RelativeLayout rootView = (RelativeLayout) inflater.inflate(R.layout.fragment_main, container, false);
            ScrollView sv = (ScrollView)rootView.getChildAt(0);
        	mTv = (TextView)sv.getChildAt(0);
            return rootView;
        }
    }

}
