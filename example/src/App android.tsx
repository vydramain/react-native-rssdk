import * as React from 'react';

// import {
//   StyleSheet,
//   View,
//   Text,
//   TouchableOpacity,
//   ScrollView,
//   FlatList,
// } from 'react-native';
// import RNFetchBlob from 'rn-fetch-blob';

import { RecordPage } from './record';
// import { MonitorPage } from './live';
// import { WIFIDevice } from './wifi';
import { useInit } from './init';
import { ScrollView, Text, TouchableOpacity } from 'react-native';
// import { Alarms } from './alarms';
// import { DeviceList } from './list';
// import { Share } from './share';
// import { QRCodeDevice } from './qrcode';
// import { PushInitLink } from './push';

export default function App() {
  const { isInit, statusText } = useInit();
  const [showInit, setShowInit] = React.useState(true);
  // const path = `file://${RNFetchBlob.fs.dirs.PictureDir}`;

  return (
    <>
      <RecordPage />
      {/* <MonitorPage isInit={isInit} /> */}
      {/* <WIFIDevice /> */}
      {/* <QRCodeDevice /> */}
      {/* <PushInitLink /> */}
      {/* <Share /> */}
      {/* <DeviceList /> */}
      {/* <Alarms /> */}
      <ScrollView
        // pointerEvents="none"
        // contentContainerStyle={{ height: 50 }}
        style={{
          position: 'absolute',
          top: 0,
          left: 0,
          right: 0,
          opacity: 1,
          backgroundColor: '#ffffff',
        }}
      >
        {showInit && (
          <>
            <Text>isInit: {isInit.toString()}</Text>
            <Text>text: {statusText?.text}</Text>
            <Text>value: {JSON.stringify(statusText?.value)}</Text>
          </>
        )}
        <TouchableOpacity
          style={{ backgroundColor: 'red' }}
          onPress={() => setShowInit((prev) => !prev)}
        >
          <Text>show/hide</Text>
        </TouchableOpacity>
      </ScrollView>
    </>
  );
}
