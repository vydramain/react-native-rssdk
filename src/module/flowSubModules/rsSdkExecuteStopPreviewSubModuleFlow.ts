import * as sdk from '../RsSdkWrapperModule';

export const rsSdkExecuteStopPreviewSubModuleFlow =
  async (session_id: string): Promise<number | undefined> => {
    try {
      return await sdk.rs_sdk_stop_preview(session_id);
    } catch (error) {
      console.error('Error occurred while RS SDK executing stop preview sub module flow with error: ', error);
    }
  };
