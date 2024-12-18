# Trade

Trading bots are able to compute thousands of orders per second (this is called High Frequency Trading)
which in return, of course, modifies the very nature of markets.

They are not merely trading spots anymore, but have become fighting arenas for various devices of artificial
intelligence.

Today, most of the transactions are processed by algorithmic trading.

The goal of this project is to create a trading bot that will bring about a revolution of the trade markets.

# Result

We start with a starting capital of $1,000 in Bitcoin.

### On the first curve, we have a profit of $231 in 2 weeks.

![image](https://github.com/user-attachments/assets/58a99366-d41e-4a78-a47b-197ef6d9a57a)

### On the second curve we have a profit of $62 in 1 week.

![image](https://github.com/user-attachments/assets/575bcbab-eea8-45cc-b323-569735a4bb63)

### On the third curve we have a profit of $55 in 1 week.

![image](https://github.com/user-attachments/assets/58eed9a1-4fab-4005-a0a2-ab6ba1916038)

# How use

To test our bot you need to use 'ai_bot_workspace'.

Download it from the [Github source](https://github.com/jmerle/ai-bot-workspace/releases/).

- If you’re on Linux, you should use ai-bot-workspace-2.4.3-x86_64.AppImage
- If you’re on Windows, you sould use ai-bot-workspace-setup-2.4.3.exe

![image](https://github.com/user-attachments/assets/109bef01-c322-424f-8386-19abe539ca51)

The executables launch ai-bot-workspace’s portal. There, you must select Crypto Trader

After go to the settings here:

![image](https://github.com/user-attachments/assets/0b3c229c-5fd3-467a-a350-69ea1a7ea801)

Now let's see the field where we need to configure.

The three main points are on the image below:

![image](https://github.com/user-attachments/assets/d1319912-160d-49a2-9ebf-5fcda78e4e68)

1) The point is the absolute path where your binary is placed.
2) The point is the place where your file .csv who contains your date is placed, but the path begin at your actual place.
3) The point is the amount of time in seconds. With the data in the directory "trade_training-datasets" we have a list of candles in USDT_BTC. So we use 3600 seconds because the tests of the subject contains 60-minutes candles for USDT_BTC trading pair. If you change this parameter the server will not accept a subject file.

# Information received by the server

The server can send informations about settings or candles or the stack.

## Settings

In this command you will receive the changes of all settings by the server.

It is possible to change:

### Interval of the candle
```
settings candle_interval 3600'
```

### Format of the candle
```
settings candle_format pair,date,high,low,open,close,volume'
```

### Total of candles
```
settings candles_total 556'
```

### Candles given
```
settings candles_given 337'
```

### Initial stack
```
settings initial_stack 1000'
```

### Transaction fee percent
```
settings transaction_fee_percent 0.2'
```
The transaction fee is compute at the moment we buy or we sell in our program.

You will receive a data like this:
```
info = ' settings ' variable value ( , value ) *
variable = string
value = string | integer
```

## Update

### Candles

When you receive this data:

**"update game next_candles USDT_BTC,1621713600,38196.54,37268.76,37286.65,38022.81,116526033.4"**.

It's an information about the actual candle.

It's represented like that:

**PAIR | DATE | HIGH | LOW | OPEN | CLOSE | VOLUME**

You need to stock it to make statistics with the list of candles you receive in all the period.

You will receive a data like this:
```
update_c = ' update game next_candles ' rate '; ' rate '; ' rate
rate = currency '_ ' currency decimal ( ' , ' decimal ) {5}
currency = 'BTC ' | ' USDT '
```

### Stack

When you receive this data **"update game stacks BTC:0.00000000,USDT:1000.00"**

You need to update your actual stack with the amount described in this data.

## Action

When you receive this data **"action order"**

The server ask you what you want to do.
You can BUY, SELL or PASS.

If you pass, the server will pass to the next candle.

How buy and sell ?

You need to answer with a strict grammar:

```
order = ' pass ' | trade_order
trade_order = ( ' buy ' | ' sell ') currency '_ ' currency decimal
currency = 'BTC ' | ' USDT '
```

In our program to buy you need to call this function
```
void Tr::Trade::buyOnMarket(double amount)
```

And for sell you need to call this function
```
void Tr::Trade::sellOnMarket(double amount)
```

If you want to pass to the next candle you can call this function
```
void Tr::Trade::pass()
```

# Training DataSet

A training file is represented like this:

![image](https://github.com/user-attachments/assets/530e4866-6cf8-46fe-bdd4-ab8a1649be2a)

Each line of the file is a candle represented like that in trading

![image](https://github.com/user-attachments/assets/d1a259a2-e581-4e43-a006-044d473a2734)

# Technicalities

- ## Transaction fee
    - by default, the bot pays a 0.2% transaction fee for each order it places

- ## Timebank :
    - allow some additional thinking time when needed
    - start the game with 10 secs
    - each time an action is requested, the timebank is increased (100-500ms)
    - the time needed by the bot to request is deducted from the timebank
    - if the bot is too slow, the timebank will be exhausted
