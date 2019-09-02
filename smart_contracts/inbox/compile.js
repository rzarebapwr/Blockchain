// Import solidity compiler
const solc = require('solc');

// Read solidity contract file, but not import it as js module
const path = require('path');
const fs = require('fs');

const inboxPath = path.resolve(__dirname, 'contracts', 'Inbox.sol');
const source = fs.readFileSync(inboxPath, 'utf8');

// Compile solidity contract, source, num of contracts in file
// and make returns vars available to import from another place
module.exports = solc.compile(source, 1).contracts[':Inbox'];


// var input = {
//     language: 'Solidity',
//     sources: {
//         'Inbox.sol' : {
//             content: source
//         }
//     },
//     settings: {
//         outputSelection: {
//             '*': {
//                 '*': [ '*' ]
//             }
//         }
//     }
// };
// console.log(JSON.parse(solc.compile(JSON.stringify(input))));
