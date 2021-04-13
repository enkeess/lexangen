### Генератор синтаксического анализатора по L-графу, соответствующему классу LL(1)-грамматик

### Входные данные 

#### Требования ко входному файлу генератора
+ Имя главного графа должно быть `_main`
+ Имена подграфов должны начинаться с символа `-` (Пример: `_C`, `_smsg_graph`, ...)
+ Поле `mark` может иметь значение `null`
+ Поле `dir` должно содержать одно из 2-х слов : `OPEN` или  `CLOSE`, для открывающих и закрывающих скобок соотвественно. 
+ Поле `id` может иметь значение `null`

Формальное описание графа в .json формате
```sh
 {
    "graph" : [
       {     
            "name" : "_string",  
            "start" : "string",   
            "end"   : ["string"],   
            "states": [  
                {  
                    "name" : "string",  
                    "transitions" : [  
                        {  
                            "to"     :  "string",  
                            "mark"   :  { 
                                "dir" : "OPEN" or "CLOSE",
                                "id"  : "sting" or null
                            },  
                            "labels" : [ "string" ]  
                        } 
                    ]
                }  
            ]  
        }  
}  
```
### Структура выходных файлов

Набор классов/хедеров для получения синтаксического анализатора:

+ `STATE_NAME.h` --- enum-множество состояний
+ `Dependencies(.h/.cpp)` - внутреннее представление входного графа.
+ `Mark(.h/.cpp)` --- класс скобочных пометок
+ `Transition(.h/.cpp)` --- класс дуг-перехода
+ `State(.h/.cpp)` --- класс состояний
+ `Scanner(.h/cpp)` --- класс лексического анализа
+ `Parser(.h/.cpp)` --- класс синтаксического анализа
+ `Makefile` --- make сборщик 

### Запуск генератора 

``` sh
git clone https://github.com/enkeess/lexangen.git
cd lexangen
make
./lexangen path
```
Пример `path`:
``` sh
./lexangen /Users/User/Documents/example/json/ex_1.json
```
Все генерируемые файлы сохраняются в папке `build` рабочей директории

### Запуск сгенерированного синтаксического анализатора
``` sh
cd build
make
./sin-analyzer path
```

Пример `path`:

``` sh
./syn-analyzer /Users/User/Documents/example/input/input.txt
```