import { ScrollView, View } from 'react-native';
import { Buttons } from './buttons';
import { styles } from '../styles';

export const PushInitLink = () => {
  return (
    <ScrollView style={styles.scrollView}>
      <Buttons />
      <View
        style={{
          width: 10,
          height: 100,
        }}
      />
    </ScrollView>
  );
};
