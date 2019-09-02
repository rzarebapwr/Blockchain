const HDWalletProvider = require('truffle-hdwallet-provider');
const Web3 = require('web3');
const { bytecode, interface } = require('./compile');

// Define a specific net provider - Rinkeby in this case
const provider = new HDWalletProvider(
  'fringe giraffe action cable kitten clap pizza system critic client update spawn',
  'https://rinkeby.infura.io/v3/0d04bbcca2d34189ae5fa60ca8033950');

const web3 = new Web3(provider);

const deploy = async () => {

  // Get list of available accounts from received seed
  accounts = await web3.eth.getAccounts();
  console.log('Using account: ', accounts[0]);

  const result = await new web3.eth.Contract(JSON.parse(interface))
     .deploy({data: '0x' + bytecode, arguments: ['Hi there!']})
     .send({from: accounts[0]}); // remove 'gas'


  console.log('Contract deployed to: ', result.options.address);

};

deploy();
