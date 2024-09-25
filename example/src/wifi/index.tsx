import { ScrollView } from 'react-native';
import { Buttons } from './buttons';
import { styles } from '../styles';

export const WIFIDevice = () => {
  return (
    <ScrollView style={styles.scrollView}>
      <Buttons />
    </ScrollView>
  );
};
