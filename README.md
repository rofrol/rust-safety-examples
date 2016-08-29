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

## More info

- http://kukuruku.co/hub/rust/comparing-rust-and-cpp
- http://www.slideshare.net/jaejukim9/rust-programming-language
- More examples https://www.reddit.com/r/rust/comments/2mwpie/what_are_the_advantages_of_rust_over_modern_c/
- UB means Undefined behaviour http://stackoverflow.com/questions/2766731/what-exactly-do-ib-and-ub-mean
- http://www.steveklabnik.com/uniq_ptr_problem/
- More Rust compared to C++ https://news.ycombinator.com/item?id=9329506
  - http://klmr.me/slides/modern-cpp/
- https://www.quora.com/What-do-C-C++-systems-programmers-think-of-Rust
- https://www.gitbook.com/book/aminb/rust-for-c

> modern C++ does nothing to protect against:
> - Iterator invalidation
> - "this" pointer invalidation
> - Dangling references
> - Use after move
> - Null pointer dereference
> pcwalton - https://news.ycombinator.com/item?id=7588801

<br>

> So caveat aside (but not ignored, it is a big issue), I see the advantages as 
> 1. No crashes because of code misuse (as long as you do not use unsafe {} ) 
> 2. No memory leaks 
> 3. No data races (so you can thread this thing like mad, but better is has async task handling (crs pattern to). So lighting up your machines cores is no prob.
> 4. Cross platform (really much better than most)
> 5. Inbuilt version management, build system and test harness (with benchmarking to).
> 6. Package management system (no more I Cannot build XX, it becomes automatic)
> 7. Inbuilt generics and traits (c++ concepts and more)
> 8. Very strongly typed (near zero runtime)
> 9. Very fast 
> 10. compiles into a c lib basically (easy integration)
> https://safenetforum.org/t/rust-vs-c/3216/2

<br>

> Like C++, Rust uses the RAII approach everywhere (Resources Acquisition Is Initialization).
> But Rust doesnt stop there. It goes a crucial step further. It wont let you access memory that was freed!
> http://www.garin.io/rust-vs-c-pitfalls

<br>

> "Rust" is composed of two languages: One that tries very hard to isolate you from the dangers of systems programming, and a more powerful one without any such aspirations.
> Unsafe Rust is a nasty, brutish language that feels a lot like C++. It allows you to do arbitrarily dangerous things, talk to the hardware, (mis-)manage memory manually, shoot yourself in the foot, etc. It is very much like C and C++ in that the correctness of the program is ultimately in your hands and the hands of all other programmers involved in it. You opt into this language with the keyword unsafe, and as in C and C++, a single mistake in a single location can bring the whole project crashing down.
> Rust has one difference to C++: It strongly encourages that memory be "shared XOR mutable", i.e., that memory is never shared and mutable at the same time. Mutate memory as you like "in the privacy of your own thread", so to speak. Contrast this with C++ where shared mutable memory is the default option and widely used.
> it is a hard guarantee that safe Rust code does not have data races (or any UB for that matter).
> http://programmers.stackexchange.com/questions/317873/how-does-rust-diverge-from-the-concurrency-facilities-of-c

<br>

> The primary advantage Rust has over idiomatic modern C++ is that it makes regular references completely safe. C++ has no equivalent for this (rvalue references are extremely limited by comparison). It obviates the need for smart pointers altogether most of the time, and prevents errors like iterator invalidation and dangling string_view that are virtually impossible to avoid in sufficiently complex C++ code. Unfortunately, most of these comparison articles do not make this point...
> http://conscientiousprogrammer.com/blog/2014/12/21/how-to-think-about-rust-ownership-versus-c-plus-plus-unique-ptr/#comment-1754897661
