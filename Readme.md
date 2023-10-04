MariaDb UDF for xxhash64, xxhash32 and xxhash32-signed
======================================================

Dependencies
------------
To compile the `mariadb-xxhash.so`, first you need to install `libxxhash-dev`.
It brings static version of the library and header files.

`
  sudo apt install libxxhash-dev
`

Build
-----
To build the `mariadb-xxhash.so` library use:

`
  make
`

If you find something is wrong with the compiling/linking feel free to edit `Makefile`
Upon success you should have a fresh copy of `mariadb-xxhash.so`, which is statically linked to `libxxhash`.

Installing
----------
Installation is just copying `mariadb-xxhash.so` to `/usr/lib/mysql/plugin`

`
  make install
`

Installing in MariaDB
---------------------
You can install the UDFs in a particular database or for the whole server.

`
  CREATE FUNCTION xxhash32 RETURNS INTEGER SONAME "mariadb-xxhash.so";
  CREATE FUNCTION xxhash32s RETURNS INTEGER SONAME "mariadb-xxhash.so";
  CREATE FUNCTION xxhash64 RETURNS INTEGER SONAME "mariadb-xxhash.so";
`

Testing in MariaDB
---------------------

```
  MariaDB> SELECT xxhash32('');
  +--------------+
  | xxhash32('') |
  +--------------+
  |     46947589 |
  +--------------+
  1 row in set (0.000 sec)
```

