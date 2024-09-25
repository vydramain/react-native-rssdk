const path = require('path');
const { getConfig } = require('react-native-builder-bob/babel-config');
const pkg = require('../package.json');

const root = path.resolve(__dirname, '..');

module.exports = getConfig(
  {
    presets: ['module:@react-native/babel-preset'],
    plugins: [
      [
        'module-resolver',
        {
          extensions: ['.tsx', '.ts', '.js', '.json'],
          alias: {
            [pkg.name]: path.join(__dirname, '..', pkg.source),
          },
        },
      ],
    ],
  },
  { root, pkg }
);
