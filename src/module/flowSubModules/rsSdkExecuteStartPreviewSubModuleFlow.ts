import * as sdk from '../RsSdkWrapperModule';
import {RsSdkStartPreviewSubModuleParams} from '../RsSdkTypes';

export const rsSdkExecuteStartPreviewSubModuleFlow =
    async (props: RsSdkStartPreviewSubModuleParams): Promise<string | undefined> => {
        try {
            return await sdk.rs_sdk_start_preview(props.device_id, JSON.stringify(props.params));
        } catch (error) {
            console.error('Error occurred while RS SDK executing start preview sub module flow with error: ', error);
        }
    };
