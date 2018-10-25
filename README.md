# Structure String
> implementation of CString

Version of C-String, but without \0

## Building
### Libraries

```sh
cd lib  # go to directory lib
mkdir build
cd build
cmake -G"Unix Makefiles" ..
make
```

### .exe files

```sh
cd examples  # go to directory examples
mkdir build
cd build
cmake -G"Unix Makefiles" ..
make
```

## Usage
AFTER Building:
```sh
cd bin  # go to directory examples
# * - is the name of the .exe file you want to run
*_runner path_to_your_input_file/filename.txt path_to_your_output_file/filename.txt
```

For instance, if you want to run second_task.exe:
```sh
second_task_runner path_to_your_input_file/filename.txt path_to_your_output_file/filename.txt
```

## Additional info

If an error occured while any function execution, it will return -1 and change errno to the corresponding error code.

## Creators

lazyTurtle21 – [Sophia Kholod](https://facebook.com/sofikholod) – kholod@ucu.edu.ua

SophiaZhyrovetska – [Sophia Zhyrovetska](https://www.facebook.com/profile.php?id=100008637310760) – zhyrovetska@ucu.edu.ua

YevheniiMoroz – [Yevhenii Moroz](https://www.facebook.com/emolodtsov) – moroz.y@ucu.edu.ua
