# Table reservation system

- C dynamic dataset project

---

## Project Structure

### main.c
- entry point, main menu.

### file.c
- file related operation - load dataset from file, save dataset to file.
- file is always saved to / loaded from current work directory and named as dataset.txt.

### prompt.c
- user input related operation - prompt for table, name, date etc.
- retry on error, empty input is allowed on query feature.

### stack.c
- stack related operation - push, pop, empty etc.

---

## How to Build

### Pre-compiled

- Get it from [GitHub action](https://github.com/black-OWL432/c-dynamic-dataset/actions).
- Download from [Nightly](https://nightly.link/black-OWL432/c-dynamic-dataset/workflows/build/master?preview) if you don't have a GitHub account.

### Custom build
- Clone the repo
```sh
git clone --depth=1 https://github.com/black-OWL432/c-dynamic-dataset.git
cd c-dynamic-dataset
```

<details>
    <summary><strong>Windows</strong></summary>
    <ul>
        <li><strong>Requirement:</strong> mingw gcc and make available in environment path.</li>
        <li>Get mingw on <a href="https://sourceforge.net/projects/mingw/files/Installer/">sourceforge</a>.</li>
        <li>Build for Windows x86_64:</li>
    </ul>
    <pre><code>make windows</code></pre>
    <ul>
        <li>Extra notes for WSL: install mingw-gcc in Ubuntu</li>
    </ul>
    <pre><code>sudo apt-get install mingw-w64</code></pre>
</details>

<details>
    <summary><strong>Linux</strong></summary>
    <ul>
        <li>Build for linux x86_64:</li>
    </ul>
    <pre><code>make linux</code></pre>
</details>

<details>
    <summary><strong>Android</strong></summary>
    <ul>
        <li><strong>Requirement:</strong> android-ndk available</li>
        <li>Build for arm64-v8a android-linux universal:</li>
    </ul>
    <pre><code>export PATH=$ANDROID_NDK_ROOT/toolchains/llvm/prebuilt/linux-x86_64/bin:$PATH
make android</code></pre>
</details>

<details>
    <summary><strong>Other platform / architecture </strong></summary>
    <ul>
        <li>Not planed, ask if you need.</li>
    </ul>
</details>
