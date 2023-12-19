# c_tools
This is a collection of tools that make my life easier when writing straight C. There is no real convention used anywhere, and things are kinda messy at the moment. 

_*You should probably not use this.*_

# Better Structs
To help with making parsing JSON in C not be an absolute boiler-plate nightmare, this tool transpiles a [metadesk](https://github.com/Dion-Systems/metadesk) file with annotated structs into a C header file that (some things not implemented):
 - [x] Can Deserialize/Serialize C structs from/to json.
 - [x] Supports `Option`al types (a-la Rust)
 - [x] Expand Rust-like enums (discriminated unions) into a similar C structure
     - [x] Serialize Enums to JSON
     - [x] Deserialize Enums
         - [x] Tagged
         - [x] Un-tagged

# The LSP Client
A very quick and dirty implementation of an LSP client that aims to be a learning experience as well as used in my modal text editor written from scratch (not in this repo...yet c:). This heavily uses `Better Structs`.

## Running the example
In the project root, just run:
```
make
```

Then in the `examples/lsp_client` directory compile and run:
```
make
./lsp_symbols <path_to_lsp_binary> <project_root_directoy> <file_to_get_symbols>
```
(NOTE: this example only supports C files right now)
