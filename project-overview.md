# Project Overview

## Introduction
The IoT Environmental Monitoring System is an embedded and network-connected prototype that measures temperature and relative humidity using a DHT11 sensor.

An ESP8266 NodeMCU reads the sensor data, connects to Wi-Fi, and hosts a local web dashboard. A browser on the same network can display the latest readings.

## Problem Statement
Temperature and relative humidity are useful environmental parameters to observe in indoor spaces. This project explores a simple way to collect these measurements and make them viewable through a browser.

## Objectives
- Interface a DHT11 with an ESP8266 NodeMCU.
- Measure temperature and relative humidity.
- Transfer readings over a local Wi-Fi network.
- Host a dashboard on the ESP8266.
- Display readings in a browser.

## Proposed Solution
The DHT11 provides readings to the ESP8266. The ESP8266 serves an HTML dashboard and a JSON endpoint. Browser-side JavaScript periodically requests the latest values.

## Scope
This version measures only temperature and relative humidity. It displays current readings locally and does not implement cloud storage, historical charts, notifications, or remote internet access.

## Project Category
Internet of Things, Embedded Systems, Wireless Sensor Monitoring, and Web-Based Data Visualization.
