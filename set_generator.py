#!/usr/bin/env python3

import numpy as np
import sys

def generate_data(num_lines):
    print("pair,date,high,low,open,close,volume")
    mu = 0.01 / (24 * 60 * 60)
    sigma = 0.1 / np.sqrt(24 * 60 * 60)
    dt = 3600
    price = 36000
    timestamp = 0
    for _ in range(num_lines):
        high = price + np.random.normal(mu * dt, sigma * np.sqrt(dt)) + np.random.normal(0, 0.01)
        low = max(price - np.random.normal(mu * dt, sigma * np.sqrt(dt)), 0) - np.random.normal(0, 0.1)
        open_price = price
        close_price = (high + low) / 2.0
        volume = np.random.randint(50_000_000, 250_000_000)

        print(f"USDT_BTC,{timestamp},{high:.2f},{low:.2f},{open_price:.2f},{close_price:.2f},{volume}")

        price += np.random.normal(mu * dt, sigma * np.sqrt(dt))
        timestamp += dt

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: set_generator.py <num_candle>")
        sys.exit(84)

    generate_data(int(sys.argv[1]))
