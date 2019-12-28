const Blockchain = require('./blockchain');
const Block = require('./block');


describe('Blockchain', () => {

    let blockchain;

    beforeEach(() => {
        blockchain = new Blockchain();
    });

    it('chain is array type', () => {
        expect(blockchain.chain instanceof Array).toBe(true);
    });

    it('starts with genesis block', () => {
        expect(blockchain.chain[0]).toEqual(Block.getGenesisBlock());
    });

    it('successfully adds new block to the blockchain', () => {
        const someData = 'data';

        blockchain.addBlock({data: someData});
        expect(blockchain.chain[blockchain.chain.length-1].data)
        .toEqual(someData);
    });

    describe('isChainValid()', () => {

        describe('chain does not starts with genesis block', () => {
            it('returns false', () => {
                blockchain.chain[0] = {data: 'fake-genesis-data'};
                expect(Blockchain.isChainValid(blockchain.chain)).toBe(false);
            });
        });

        // describe('when chain starts with genesis and multiple block after', () => {
        //     beforeEach(() => {
        //         blockchain.addBlock({data: 'somedata1'})
        //         blockchain.addBlock({data: 'somedata2'})
        //         blockchain.addBlock({data: 'somedata3'})
        //     });


        //     describe('lastHash reference has changed', () => {
        //         it('returns false', () => {
        //             blockchain.chain[2].lastHash = 'broken-hash';
        //             expect(Blockchain.isChainValid(blockchcain.chain)).toBe(false);
        //         });
        //     });

        //     describe('any block data was changed', () => {
        //         it('returns false', () => {
        //             blockchain.chain[2].data = 'broken-data';
        //             expect(Blockchain.isChainValid(blockchcain.chain)).toBe(false);
        //         });
        //     });

        //     describe('validated chain', () => {
        //         it('returns true', () => {
        //             expect(Blockchain.isChainValid(blockchain.chain)).toBe(true);
        //         });
        //     });
        // });
    });
});