// import React from 'react';
import // StyleSheet,
// Text,
// TouchableOpacity,
// ScrollView,
// View,
'react-native';

// import { DEVICE_ID } from '../topsecret';

// const Button = ({ onPress, text }: { onPress: () => void; text: string }) => {
//   return (
//     <TouchableOpacity onPress={onPress} style={styles.button}>
//       <Text style={styles.buttonText}>{text}</Text>
//     </TouchableOpacity>
//   );
// };

export const RecordButtons = ({}: // playerRef,
// setTimeline,
{
  // playerRef: RecordPlayerRef | null;
  // setTimeline: React.Dispatch<React.SetStateAction<number[] | null>>;
}) => {
  return null;
  // const loadChannelsInfo = async () => {
  //   try {
  //     const info = await getChannelInfo({ deviceId: DEVICE_ID });
  //     console.log('channels info is: ', info);
  //   } catch (error) {
  //     console.log('loadChannelsInfo error: ', error);
  //   }
  // };

  // const loadChannelsCount = async () => {
  //   try {
  //     const count = await getChannelCount({ deviceId: DEVICE_ID });
  //     console.log('channels count is: ', count);
  //   } catch (error) {
  //     console.log('loadChannelCount error: ', error);
  //   }
  // };

  // const searchRecordByFile = () => {
  //   // 1000 - 1 мс
  //   // 60 - 1 минута
  //   // 60 - 1 час
  //   // 24 - 1 сутки
  //   // 3 - 3 дня
  //   const start = Date.now() - 1000 * 60 * 60 * 24 * 2;
  //   const end = Date.now() - 1000 * 60 * 60 * 24;

  //   playerRef?.searchRecordByFile(start, end);
  // };

  // const startPlayRecordByTime = () => {
  //   const start = 1699767174000;
  //   const end = 1699853574000;
  //   // const start = 1698365090000;
  //   // const end = 1698608819000;
  //   playerRef?.startPlayRecordByTime(start, end);
  // };

  // const searchRecordTimeInfo = async () => {
  //   try {
  //     // 27.10.23
  //     // const start = 1698364800000;
  //     // const start = 1698364800000;
  //     const start = 1699680774000;

  //     const result = await searchTimeinfo({
  //       deviceId: DEVICE_ID,
  //       time: start,
  //       deviceChannel: 0,
  //       fileType: 0,
  //       streamType: 0,
  //       seq: 0,
  //     });
  //     // const result2 = await searchTimeinfo({
  //     //   deviceId: DEVICE_ID,
  //     //   startTime: start - 10000,
  //     //   endTime: start,
  //     //   deviceChannel: 0,
  //     //   fileType: 0,
  //     //   streamType: 0,
  //     //   seq: 0,
  //     // });
  //     if (result?.minutesStatusList) {
  //       setTimeline(result?.minutesStatusList);
  //     }

  //     console.log('searchRecordTimeInfo result: ', result);
  //     // console.log('searchRecordTimeInfo result2: ', result2);
  //   } catch (error) {
  //     console.log('searchRecordTimeInfo error: ', error);
  //   }
  // };

  // const openVoice = () => {
  //   playerRef?.openVoice();
  // };

  // const closeVoice = () => {
  //   playerRef?.closeVoice();
  // };

  // const pause = () => {
  //   playerRef?.pausePlay();
  // };

  // const rePlay = () => {
  //   playerRef?.rePlay();
  // };

  // const stopPlay = () => {
  //   playerRef?.stopPlay();
  // };

  // const testFunc = () => {
  //   // playerRef.;
  // };
  // // const updateSpeed = (speed: number) => {
  // //   playerRef?.setPlaySpeed(speed);
  // // };

  // const init = () => {
  //   console.log('playerRef: ', playerRef);
  //   playerRef?.init();
  // };

  // const test = () => {
  //   // startSetWiFi({ passwordWifi: '' });
  // };

  // return (
  //   // <ScrollView
  //   //   style={{
  //   //     backgroundColor: '#EFEFEF',
  //   //     flex: 1,
  //   //   }}
  //   // >
  //   <View style={styles.view}>
  //     <Button
  //       text="startPlayRecordByTime"
  //       onPress={() => startPlayRecordByTime()}
  //     />
  //     <Button
  //       text="searchRecordTimeInfo"
  //       onPress={() => searchRecordTimeInfo()}
  //     />
  //     <Button text="loadChannelsCount" onPress={() => loadChannelsCount()} />
  //     <Button text="loadChannelsInfo" onPress={() => loadChannelsInfo()} />
  //     <Button text="searchRecordByFile" onPress={() => searchRecordByFile()} />
  //     <Button text="openVoice" onPress={() => openVoice()} />
  //     <Button text="closeVoice" onPress={() => closeVoice()} />
  //     <Button text="testmethods" onPress={() => testFunc()} />
  //     <Button text="pause" onPress={() => pause()} />
  //     <Button text="rePlay" onPress={() => rePlay()} />
  //     <Button text="stopPlay" onPress={() => stopPlay()} />
  //     <Button text="init" onPress={() => init()} />
  //     <Button text="test" onPress={() => test()} />
  //     {/* <Button text="slow" onPress={() => updateSpeed(-3)} />
  //     <Button text="normal" onPress={() => updateSpeed(0)} />
  //     <Button text="fast" onPress={() => updateSpeed(3)} /> */}
  //   </View>
  //   // </ScrollView>
  // );
};

// const styles = StyleSheet.create({
//   container: {
//     flex: 1,
//     backgroundColor: 'pink',
//   },
//   box: {
//     width: 60,
//     height: 60,
//     marginVertical: 20,
//     padding: 20,
//   },
//   monitor: {
//     width: '100%',
//     aspectRatio: 16 / 9,
//     backgroundColor: 'yellow',
//   },
//   button: {
//     // width: 100,
//     // height: 50,
//     margin: 10,
//     padding: 10,
//     display: 'flex',
//     justifyContent: 'center',
//     alignItems: 'center',
//     backgroundColor: 'green',
//   },
//   buttonText: {
//     color: 'white',
//   },
//   view: {
//     flexDirection: 'row',
//     flexWrap: 'wrap',
//     justifyContent: 'center',
//     backgroundColor: '#EFEFEF',
//   },
// });
