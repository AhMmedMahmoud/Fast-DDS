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

# Fast DDS Libraries / Generator:
- foonathan_memory_vendor, an STL compatible C++ memory allocator library.
- fastcdr, a C++ library that serializes according to the standard CDR serialization mechanism.
- fastdds, the core library of eProsima Fast DDS library.
- fastdds_gen, a Java application that generates source code using the data types defined in an IDL file.

# Most Quick and Easy Installation Way
- fast dds provides prebuilt versions. each version is a tar file that contains a script that builds and install fast dds libraries & generator

``` bash
# step 1 : download any version from https://eprosima.com/index.php/downloads-all
# step 2 : decompressed the downloaded tar file using tar -xf <FILE_NAME>
# step 3 : know what options the script provides
./install --help
# step 4 : run with your wanted options
sudo ./install --install-prefix <INSTALLATION_PATH> --build-cores <NO_OF_CORES>
```
