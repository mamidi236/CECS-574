# CECS-574
Parallel Word counter using Open MP and MPI

The word counting which MapReduce can handle in parallel. The goal of this program is to show how many times each word appears in the given list of words (or text). The word serves as the key and the number one serves as the data when viewing the input as tuples. All occurrences of a term would be gathered by a basic map function into an equivalence class.. The function that carries out this optimization is known as a combiner in Google terminology and runs on the same process as the map. This is significant because it serves the purpose of reducing the amount of communicated data required between the map and reduce stages by combining several members of an equivalence class into a single member.


# OpenMP version :  
There will be four kinds of threads:
Reader threads, Mapper Mapper threads, Reducer threads, Writer threads
Different writer threads run at various times. Within a node, it is possible to schedule the Mapper and Reducer threads to execute at various times. By taking various pieces of work out of work queues, these threads may be created to do various jobs. Each reducer thread has its own work queue. Items for work will be added to this queue by mapper threads.All keys that map onto reducer g should be added to g’s work queue.Each process can assume it will be receiving data from every other node. This will simplify the communication structure of the program when we use the MPI version. A node that sends no data should send an “empty” record letting the other process no it will get no data from it. As each process finishes its reduced work, it should write its results to an output file, close it, and notify the master thread that it is finished so that it can terminate the job, and then terminate itself. 


# MP Version :
The MPI version will use multiple nodes. Each node will run a copy of the OpenMP code above to perform local computations. A few changes need to be made to the OpenMP process on a node to communicate with the OpenMP processes running on other nodes. Instead of mappers putting their results onto a reducers work queue,  a list to be sent to other nodes. A sender thread is  used to send the results of reducers in these lists to the appropriate node. Each node  receiver thread that obtains data sent to it by sender threads in other nodes The receiver thread for a node will place its received data onto work queues in the node for each reducer.Each node will read some portion of the input files. We could statically define the files each node will process, but this might lead to some nodes getting many big files and other nodes getting many small files. Instead, each node should request a file from a master node which will either send a filename back to the node or an “all done” that indicates that all files have been or are being processed.


# Outcomes :
Compare the performance analysis on openMP and MPI version. By speedup numbers when using 1,2,4 .. cores Mapper and Reader threads with nodes to run the program with mapper and reader thread for each core on a node.


# Results :   

###### openMP    
The data in the following table are average run time of 10 runs with same input but different number of cores

| Cores      | 2     | 4     | 8     | 16    |
| ---------- | ----- | ----- | ----- | ----- |
| Speedup    | 1.734 | 2.883 | 2.586 | 2.093 |
| Efficiency | 0.867 | 0.721 | 0.323 | 0.131 |
| Karp-Flatt | 0.153 | 0.129 | 0.299 | 0.443 |


###### MPI   
The data in the following table are average run time of 10 runs with same input but different number of cores

| Cores      | 2     | 4     | 8     | 16    |
| ---------- | ----- | ----- | ----- | ----- |
| Speedup    | 1.175 | 1.356 | 1.475 | 1.308 |
| Efficiency | 0.588 | 0.339 | 0.184 | 0.082 |
| Karp-Flatt | 0.702 | 0.650 | 0.632 | 0.749 |




# Conclusion :    
OpenMP has higher efficiency and better performance and it is easier to implement the algorithm. MPI version, due to larger overhead of communication between the nodes and trickier algorithm to manipulate the hash table, has a little speedup but is tiny when compared with OpenMP. The reason why MPI performs badly is because the hash table was implemented locally and did the combination and reduction in order over time. However, the shared memory is used globally in the OpenMP so that every thread can access it.






