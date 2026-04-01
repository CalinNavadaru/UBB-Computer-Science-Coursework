import java.lang.management.ManagementFactory

def threadMXBean = ManagementFactory.getThreadMXBean()

// Detectare deadlock-uri
def deadlockedThreads = threadMXBean.findDeadlockedThreads()

if (deadlockedThreads) {
    println "=== Deadlock Detected! ==="
    def threadInfos = threadMXBean.getThreadInfo(deadlockedThreads)
    threadInfos.each { threadInfo ->
        println "Thread: ${threadInfo.threadName} (ID: ${threadInfo.threadId})"
        println "State: ${threadInfo.threadState}"
        println "Stack Trace:"
        threadInfo.stackTrace.each { println "\tat ${it}" }
        println "-----------------------------"
    }
} else {
    println "No deadlocks detected."
}

// Dump-ul complet al thread-urilor
def threadInfos = threadMXBean.dumpAllThreads(true, true)
println "=== Thread Dump ==="
threadInfos.each { threadInfo ->
    println "Thread: ${threadInfo.threadName} (ID: ${threadInfo.threadId})"
    println "State: ${threadInfo.threadState}"
    threadInfo.stackTrace.each { stackFrame ->
        println "\tat ${stackFrame}"
    }
    println "-----------------------------"
}
