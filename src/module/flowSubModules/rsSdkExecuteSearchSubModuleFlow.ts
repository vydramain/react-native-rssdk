import * as sdk from '../RsSdkWrapperModule';
import {RsSdkOemTypeEnum} from '../RsSdkEnums';
import {RsSdkSearchSubModuleResponse} from '../RsSdkTypes';

export const rsSdkExecuteSearchSubModuleFlow =
    async (): Promise<RsSdkSearchSubModuleResponse | undefined> => {
        try {
            const search_result = await sdk.rs_sdk_search_device(
                JSON.stringify({'oem type': RsSdkOemTypeEnum.optimus}));

            return JSON.parse(search_result);
        } catch (error) {
            console.error('Error occurred while RS SDK executing search sub module flow with error: ', error);
        }
    };
