const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');

module.exports = {
  entry: './src/index.js',  // your main React file
  output: {
    path: path.resolve(__dirname, 'dist'), // folder where bundled code goes
    filename: 'bundle.js',
    clean: true, // clears dist folder before each build
  },
  module: {
    rules: [
      {
        test: /\.(js|jsx)$/,       // all .js and .jsx files
        exclude: /node_modules/,
        use: {
          loader: 'babel-loader',  // uses Babel to transpile
        },
        
      },
      {
  test: /\.(png|jpe?g|gif|svg)$/i,
  type: 'asset/resource',
},

      {
    test: /\.css$/,
    use: ['style-loader', 'css-loader'],
  },
    ],
  },
  resolve: {
    extensions: ['.js', '.jsx'], // allows imports without extensions
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: './public/index.html', // HTML template
    }),
  ],
  devServer: {
    static: path.join(__dirname, 'dist'),
    port: 3000,
    open: true,
    hot: true,
  },
  mode: 'development',
};
