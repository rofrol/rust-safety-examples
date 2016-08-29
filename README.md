- Examples from http://www.slideshare.net/jaejukim9/rust-programming-language
  - https://news.ycombinator.com/item?id=7588801
- More https://www.reddit.com/r/rust/comments/2mwpie/what_are_the_advantages_of_rust_over_modern_c/
- UB explanation http://stackoverflow.com/questions/2766731/what-exactly-do-ib-and-ub-mean

## Use after free

C version

```bash
$ gcc use_after_free.c
# prints nothing
$ ./a.out
```

## Dangling pointer

C version

```bash
$ gcc dangling_pointer.c
dangling_pointer.c: In function another_dump_function:
dangling_pointer.c:6:5: warning: function returns address of local variable [-Wreturn-local-addr]
     return &a_local_variable;
     ^
```

Rust version

```bash
$ rustc dangling_pointer.rs
dangling_pointer.rs:1:25: 1:29 error: missing lifetime specifier [E0106]
dangling_pointer.rs:1 fn a_dump_function() -> &i32 {
                                              ^~~~
dangling_pointer.rs:1:25: 1:29 help: run `rustc --explain E0106` to see a detailed explanation
dangling_pointer.rs:1:25: 1:29 help: this function's return type contains a borrowed value, but there is no value for it to be borrowed from
dangling_pointer.rs:1:25: 1:29 help: consider giving it a 'static lifetime
error: aborting due to previous error
```

## Iterator invalidation

C++ version

```bash
$ g++ iterator_invalidation.cpp
$ ./a.out
Segmentation fault (core dumped)
```

Rust version

```bash
$ rustc iterator_invalidation.rs
iterator_invalidation.rs:5:5: 5:6 error: cannot borrow `v` as mutable because it is also borrowed as immutable [E0502]
iterator_invalidation.rs:5     v.push("world");
                               ^
iterator_invalidation.rs:4:14: 4:15 note: immutable borrow occurs here
iterator_invalidation.rs:4     let x = &v[0];
                                        ^
iterator_invalidation.rs:7:1: 7:2 note: immutable borrow ends here
iterator_invalidation.rs:7 }
                           ^
iterator_invalidation.rs:5:5: 5:6 help: run `rustc --explain E0502` to see a detailed explanation
error: aborting due to previous error
```
