const assert = require('assert');
const ganache = require('ganache-cli');
const Web3 = require('web3');
const {bytecode, interface} = require('../compile');

const web3 = new Web3(ganache.provider());

// Define global vars to be available in tests uints
let accounts;
let inbox;

beforeEach(async () => {

  // Get list of available accounts using await - getAccounts is async method
  accounts = await web3.eth.getAccounts();

  // Use one of the accounts to deploy contract
  inbox = await new web3.eth.Contract(JSON.parse(interface))
  .deploy({ data: bytecode, arguments: ['Hi there']})
  .send({ from: accounts[0], gas: '1000000'})
});


describe('Inbox', () => {

  it('deploys a contract', () => {
    console.log(inbox.options.address);
  });

  it('has initialized message', async () => {
    const message = await inbox.methods.message().call();
    assert.equal(message, 'Hi there');
  });

  it('can change contract attribute', async () => {
    await inbox.methods.setMessage('Hey You!').send({ from: accounts[0]});
    const message = await inbox.methods.message().call();
    assert.equal(message, 'Hey You!');
  })


});
