#![no_std]
#[cfg(feature = "alloc")]
extern crate alloc;
#[cfg(feature = "alloc")]
pub use portal_corkel_wasm_alloc::CkAllocator;
