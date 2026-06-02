# WakeGuard

## Team Members
- อภิญรฎา แป้งนวล (Project Manager)
- อนันดา สมใจ (UX/UI Designer)
- ปรียาภรณ์ เดชพันธ์ (IoT Developer)

## Problem
ผู้ขับขี่อาจเกิดอาการง่วงจากระดับ CO₂ ภายในรถที่สูงเกินไป

## Core Flow
ผู้ขับขี่อยู่ภายในรถ
→ SCD40 ตรวจวัดค่า CO₂
→ ESP32 ประมวลผลค่า
→ RGB LED แจ้งเตือนระดับความเสี่ยง
→ ผู้ขับขี่รับรู้สถานะอากาศ

## Sprint Goal
ESP32 สามารถอ่านค่า CO₂ จาก SCD40
และแสดงผลการแจ้งเตือนผ่าน RGB LED

## Current Status
- Firmware Prototype Complete
- Hardware Integration Partial
- RGB LED Replacement Required

## Repository Structure
docs/
hardware/
firmware/
design/
evidence/
