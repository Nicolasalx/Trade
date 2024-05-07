/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-groundhog-thibaud.cathala
** File description:
** groundhog
*/

#ifndef TRADE_HPP_
    #define TRADE_HPP_

    #include "vector"
    #include <ctime> 
    #include <string>
    #include <iostream>
    #include <cctype>
    #include <map>

namespace Tr
{
    class Trade
    {
        enum action_e {
            BUY,
            SELL,
            PASS
        };
        enum candle_format_e {
            PAIR,
            DATE,
            HIGH,
            LOW,
            OPEN,
            CLOSE,
            VOLUME
        };

        struct settings_t {
            std::string player_names = "";
            std::string your_bot = ""; // Check surement relié au player name
            std::size_t timebank = 0;
            std::size_t time_per_move = 0;
            std::size_t candle_interval = 0;
            std::string candle_format = ""; // Change la facon dont on parse
            std::size_t candles_total = 0;
            std::size_t candles_given = 0;
            std::size_t initial_stack = 0;
            double transaction_fee_percent = 0.0;
        };

        struct signal_t {
            action_e action = PASS;
            double amount = 0.0;    
        };

        struct stack_t {
            double BTC = 0.0;
            double USDT = 0.0;
        };

        struct statistics_t {
            double lastMMShort = 0.0;
            double lastMMLong = 0.0;
        };

        struct candle_t {
            long int date;
            long double high = 0.0;
            long double low = 0.0;
            long double open = 0.0;
            long double close = 0.0;
            long double volume = 0.0;

            statistics_t stats;
        };

        public:
            Trade() = default;
            ~Trade() = default;

            // Loop global
            void engineTrading();

            // Parsing input market
            void parseInputMarket();
            void selectCommand(const std::string &input);
            void initCandleFormat();

            // Update command
            void manageAnUpdate(std::vector<std::string> lineTokens);

            // Add new candle (Update command)
            void addCandle(const std::string &inputCandle);
            void addCryptoCandle(const std::string &cryptoLine);
            void setPairToCandle(const std::string &pairName);

            // Handle stacks (Update Command)
            void handleStacks(const std::string &inputStacks);
            void setAmountToOneCrypto(const std::string &dataCrypto);

            // Settings command
            void manageSettings(std::vector<std::string> lineTokens);
            void changeFormatCandle(const std::string &inputFormat);

            // Action command
            void manageAnAction();
            void checkSignal();

            // Buy and Sell
            void buyOnMarket(double amount);
            void sellOnMarket(double amount);
            void orderAction(const std::string &pair, double amount, action_e action);

            void increaseAmount(const std::string &currency, double amount);
            void decreaseAmount(const std::string &currency, double amount);

            void getPairName(std::string &namePair);
            void pass();

            // ! Statistics

            // Moving Average Short and Long
            void computeShortMovingAverage();
            double computeMovingAverage(std::vector<candle_t> candlesCrypto, int period);
            void computeLongMovingAverage();
            void checkMMLongAndShort();
            void checkOnePair();

            // Boolinger Bands
            void computeBollingerBands();
            double computeStandardDeviation(std::vector<candle_t> candlesCrypto, std::size_t period);

            void checkOnePairBolBand(std::size_t period, double inputMoney, double outputMoney);

            // Utils
            int getInt(const std::string &input);
            double getDouble(const std::string &input);

        private:
            std::vector <candle_t> _listCandles;
            std::vector<candle_format_e> _candleFormat;
            settings_t _settings;
            stack_t _stack;
            bool _stopLoop = false;
            signal_t _signal;
    };
}

#endif /* !TRADE_HPP_ */