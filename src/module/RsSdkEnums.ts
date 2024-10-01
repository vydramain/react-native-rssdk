export enum RsSdkP2PTypeEnum {
    IP = 'ip',
    TUTK = 'tutk',
    VV = 'vv',
    RSVV = 'rsvv',
    RS = 'rs',
}

export enum RsSdkOemTypeEnum {
    default = 'default',
    optimus = 'optimus'
}

export enum RsSdkProtocolEnum {
    auto = 'auto',
    http = 'http',
    https = 'https',
    media = 'media'
}

export enum RsSdkConnctionCallbackEnum {
    success = 'success',
    connecting = 'connecting',
    close = 'close',
    unknown_error = 'unknown error',
    user_logined = 'user logined',
    user_or_password_error = 'user or password error',
    user_no_right = 'user no right',
    ip_filter = 'ip filter',
    max_user = 'max user',
    user_disabled = 'user disabled',
    force_change_password = 'force change password',
    force_close_brower = 'force close brower',
    forbidden_ip = 'forbidden ip',
    p2p_mode = 'p2p mode',
    relay_mode = 'relay mode',
    lan_mode = 'lan mode',
    login_failed_or_block = 'login_failed_or_block',
}

export enum RsSdkStreamTypeEnum {
    main_stream = 'main stream',
    sub_stream = 'sub stream',
    mobile_stream = 'mobile stream'
}
