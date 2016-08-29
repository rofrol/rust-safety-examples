fn a_dump_function() -> &i32 {
    let local_variable: i32;
    &local_variable;
}

fn main() {
    let raw_pointer = a_dump_function();
    *raw_pointer = 123
}
