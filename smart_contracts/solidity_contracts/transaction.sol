pragma solidity >=0.4.22 <0.7.0;


contract Transaction {

    event SenderLogger(address);
    event ValueLogger(uint);

    address private owner;

    modifier isOwner {
        require(msg.sender == owner, "Only owner can call it");
        _;
    }

    modifier validValue {
        require(msg.value >= 1 ether);
        _;
    }

    constructor() public {
        owner = msg.sender;
    }

    function hey() public payable isOwner validValue {
        emit SenderLogger(msg.sender);
        emit ValueLogger(msg.value);
    }
} 
