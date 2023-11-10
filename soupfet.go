package main

import (
	"fmt"
	"os"
	"runtime"
	"strings"
)

var (
	red    = "\033[31m"
	yellow = "\033[33m"
	blue   = "\033[34m"
	purple = "\033[35m"
	reset  = "\033[0m"
)

func bunny() {
	fmt.Printf(`
  /\__/\
  ( . .)
  c(%s"%s)(%s"%s)
%s`, red, reset, red, reset, "\n")
}

func osName() string {
	var releaseFile []byte
	if temp, err := os.ReadFile("/etc/os-release"); err == nil {
		releaseFile = temp

	} else if temp, err := os.ReadFile("/etc/lsb-release"); err == nil {
		releaseFile = temp
	} else {
		return runtime.GOOS
	}
	firstLine := strings.Split(string(releaseFile), "\n")[0]
	name := strings.Split(firstLine, "=")[1]
	return strings.ReplaceAll(name, "\"", "")
}

func kernel() string {
	version, _ := os.ReadFile("/proc/version")
	return strings.Split(string(version), " ")[2]
}

func shell() string {
	sh := strings.Split(os.Getenv("SHELL"), "/")
	return sh[len(sh)-1]
}

func main() {
	username := os.Getenv("USER")
	hostname, _ := os.Hostname()
	session := os.Getenv("DESKTOP_SESSION")

	bunny()
	fmt.Println(red + username + reset + "@" + red + hostname)
	fmt.Println(purple + "OS  " + reset + osName())
	fmt.Println(yellow + "Kernel  " + reset + kernel())
	fmt.Println(blue + "Shell  " + reset + shell())
	fmt.Println(purple + "Session  " + reset + session + "\n")
}
