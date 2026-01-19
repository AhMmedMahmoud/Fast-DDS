# Fast-DDS
# introduction
- DDS is a protocol (specification) defined by the Object Management Group (OMG)
- Fast DDS is a C++ implementation of the DDS Specification.
- Fast DDS library provides both an Application Programming Interface (API) and a communication protocol that deploy a Data-Centric Publisher-Subscriber (DCPS) model

Fast DDS comprises:
- The DDS API implementation.
- Fast DDS-Gen, a generation tool for bridging typed interfaces with the middleware implementation.
- The underlying RTPS wire protocol implementation.

# Conceptual diagram
<img width="610" height="207" alt="image" src="https://github.com/user-attachments/assets/e6e21a07-a67a-493e-a437-1a10fc46a368" />

## Terms for DDS
- Topic : an identifer that publisher and subscriber should agree on it (imagine it as switch that connect all applications that attached to it) (unique per domain)
- Publisher: data sender
- Subscriber: data receiver
- Domain: similar to a meeting room contains communication partners
- DomainParticipant: (communication entity or communication partner) application that can be publisher or subscriber or both

## notes
- Only entities belonging to the same domain can discover each other through matching topics, and consequently exchange data between publishers and subscribers
- The information flow is regulated by Quality of Service (QoS) policies established between the entities in charge of the data exchange.

# Dependencies
``` bash
sudo apt install cmake g++ python3-pip wget git
sudo apt install libasio-dev libtinyxml2-dev
sudo apt install libssl-dev
```

# installing eProsima Fast DDS:
- foonathan_memory_vendor, an STL compatible C++ memory allocator library.
- fastcdr, a C++ library that serializes according to the standard CDR serialization mechanism.
- fastdds, the core library of eProsima Fast DDS library.
- fastdds_gen, a Java application that generates source code using the data types defined in an IDL file.

``` bash
# Foonathan memory
cd ~/Fast-DDS-python
git clone https://github.com/eProsima/foonathan_memory_vendor.git
mkdir foonathan_memory_vendor/build
cd foonathan_memory_vendor/build
cmake .. -DCMAKE_INSTALL_PREFIX=~/Fast-DDS-python/install -DBUILD_SHARED_LIBS=ON
cmake --build . --target install

# Fast CDR
cd ~/Fast-DDS-python
git clone https://github.com/eProsima/Fast-CDR.git
mkdir Fast-CDR/build
cd Fast-CDR/build
cmake .. -DCMAKE_INSTALL_PREFIX=~/Fast-DDS-python/install
cmake --build . --target install

# Fast DDS
cd ~/Fast-DDS-python
git clone https://github.com/eProsima/Fast-DDS.git
mkdir Fast-DDS/build
cd Fast-DDS/build
cmake .. -DCMAKE_INSTALL_PREFIX=~/Fast-DDS-python/install
cmake --build . --target install

# Fast DDS Python bindings
cd ~/Fast-DDS-python
git clone https://github.com/eProsima/Fast-DDS-python.git
mkdir -p Fast-DDS-python/fastdds_python/build
cd Fast-DDS-python/fastdds_python/build
cmake ..  -DCMAKE_INSTALL_PREFIX=~/Fast-DDS-python/install
cmake --build . --target install
```
