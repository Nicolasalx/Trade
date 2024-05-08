/*
** EPITECH PROJECT, 2024
** Trade
** File description:
** addCandle
*/

#include "trade.hpp"
#include "my_tracked_exception.hpp"
#include "split_string.hpp"

void Tr::Trade::setPairToCandle(const std::string &pairName)
{
    if (pairName != "USDT_BTC") {
        throw my::tracked_exception("Parsing Input: In the add of a candle in one crypto, a pair has not been recognized!");
    }
}

void Tr::Trade::addCryptoCandle(const std::string &cryptoLine)
{
    candle_t candle;
    std::vector<std::string> dataCrypto;
    my::split_string(cryptoLine, ",", dataCrypto);

    if (dataCrypto.size() != 7) {
        throw my::tracked_exception("Parsing Input: In the add of a candle in one crypto the number of arguments delimited by ',' need to be at 7!");
    }
    for (std::size_t i = 0; i < 7; ++i) {
        if (_candleFormat.at(i) == PAIR) {
            setPairToCandle(dataCrypto.at(i));
        } else if (_candleFormat.at(i) == DATE) {
            candle.date = getInt(dataCrypto.at(i));
        } else if (_candleFormat.at(i) == HIGH) {
            candle.high = getDouble(dataCrypto.at(i));
        } else if (_candleFormat.at(i) == LOW) {
            candle.low = getDouble(dataCrypto.at(i));
        } else if (_candleFormat.at(i) == OPEN) {
            candle.open = getDouble(dataCrypto.at(i));
        } else if (_candleFormat.at(i) == CLOSE) {
            candle.close = getDouble(dataCrypto.at(i));
        } else if (_candleFormat.at(i) == VOLUME) {
            candle.volume = getDouble(dataCrypto.at(i));            
        }
    }
    _listCandles.push_back(candle);
}
