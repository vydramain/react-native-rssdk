package com.monitoring.optimus.rs.jni;

public interface JniRsSdkCallback {
    void connction_callback(String param);

    void alarm_callback(String alarm_type,String param);

    void search_record_month_callback(String param);

    void search_record_day_callback(String param);

    void search_device_callback(String param);

    void preview_callback(String param);
}
