# rZone--RaspberryGate--WDT/Arduinosketch_20220111_newWDT

Watchdog Timers for Raspberry Gate


    sketch_20220111_newWDT
     ├── README.md
     ├── mydefs.h                    // common definitions
     ├── sketch_20220111_newWDT.ino  // main sketch
     ├── taskClass0.cpp              // task0
     ├── taskClass0.h                // task0 header
     ├── taskClass1.cpp              // task1
     ├── taskClass1.h                // task1 header
     ├── taskClass2.cpp              // task2
     ├── taskClass2.h                // task2
     ├── taskClass3.cpp              // task3 header
     ├── taskClass3.h                // task3
     ├── taskClass4.cpp              // task4
     ├── taskClass4.h                // task4 header
     └── tasks.ino                   // other tasks

     0 directories, 15 files (Thu Jan 13 09:35:17 JST 2022)


task0 - Check the "heart beat" pulse from Raspberry Pi

task1 - Blink LED to show the current status

task2 - Detect type-specified request from Raspberry Pi

task3 - Generate RESET pulse (for both of the gentle and the delayed watchdog)

task4 - Generate notification signal for Raspberry Pi

taskX - Blink LED using the notification pin (for debugging)
